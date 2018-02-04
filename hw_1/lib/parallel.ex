defmodule Parallel do
  @moduledoc """
  Parallel map implementation.

  One should connect nodes manually before running `Parallel.map`.
  By default only host node is used.

  ## Examples

      iex(main@hostname)1> Node.connect :foo@hostname
      true
      iex(main@hostname)2> Node.connect :bar@hostname
      true
      iex(main@hostname)3> Parallel.map(&Parallel.Test.fac/1, [5, 1, 2])
      [120, 1, 2]

  """

  @type element :: any

  import Stream,    only: [cycle: 1, zip: 2]
  import Enum,      only: [to_list: 1]
  import List,      only: [foldr: 3]
  import Recursion, only: [fix: 1]

  @doc """
  Parallel map itself.

  ## Examples

      iex> Parallel.map(&Parallel.Examples.fac/1, [5, 1, 2])
      [120, 1, 2]

  """
  @spec map((element -> any), Enumerable.t()) :: Enumerable.t()
  def map(func, list) do
    nodes = [node() | Node.list()]
    tasks = Stream.map(zip(list, cycle(nodes)), fn {elem, node} ->
      # IO.puts("Starting function on node " <> to_string(node))
      Task.Supervisor.async({Parallel, node}, fn ->
        func.(elem)
      end)
    end)

    loop = fn loop ->
      fn tasks ->
        # foldl over task list, second element of tuple is `true`
        # if the elements of `tasks` are all results and not task
        # structures
        case foldr(tasks, {[], true}, fn elem, {acc, no_tasks} ->
              case elem do
                %Task{} ->
                  result = Task.yield(elem)
                  if result do
                    {[result | acc], no_tasks}
                  else
                    {[elem | acc], false}
                  end
                _       -> {[elem | acc], no_tasks}
              end
            end) do
          {list, true}  -> list
          {list, false} -> loop.(list)
        end
      end
    end

    Enum.map(fix(loop).(to_list(tasks)), fn {:ok, res} -> res end)
  end
end
