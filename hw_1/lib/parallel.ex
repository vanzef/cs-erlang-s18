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

  import List,      only: [foldr: 3]
  import Recursion, only: [fix: 1]

  alias Task.Supervisor, as: TS
  alias Parallel.NodePicker, as: PNP

  @doc """
  Parallel map itself.

  ## Examples

      iex> Parallel.map(&Parallel.Examples.fac/1, [5, 1, 2])
      [120, 1, 2]

  """
  @spec map((element -> any), Enumerable.t()) :: Enumerable.t()
  def map(func, list) do
    {:ok, picker} = PNP.start_link([])
    tasks = Enum.map(list, fn elem ->
      node = PNP.get(picker)
      # IO.puts("spawn " <> to_string(node))
      {
        elem,
        node,
        TS.async_nolink({Parallel, node}, fn ->
          func.(elem)
        end)
      }
    end)

    loop = fn loop ->
      fn tasks ->
        # foldl over task list, second element of tuple is `true`
        # if the elements of `tasks` are all results and not task
        # structures
        case foldr(tasks, {[], true}, fn {elem, node, task}, {acc, no_tasks} ->
              case task do
                %Task{} ->
                  # check if node is still alive
                  case Node.ping node do
                    :pong ->
                      result = Task.yield(task)
                      if result do
                        {[{elem, node, result} | acc], no_tasks}
                      else
                        {[{elem, node, task} | acc], false}
                      end
                    :pang ->
                      # respawn task
                      node = PNP.get(picker)
                      # IO.puts("respawn " <> to_string(node))
                      task = TS.async_nolink({Parallel, node}, fn ->
                        func.(elem)
                      end)
                      {[{elem, node, task} | acc], false}
                  end
                _       -> {[{elem, node, task} | acc], no_tasks}
              end
            end) do
          {list, true}  -> list
          {list, false} -> loop.(list)
        end
      end
    end

    Enum.map(fix(loop).(tasks), fn {_, _, {:ok, res}} -> res end)
  end
end
