defmodule Parallel.NodePicker do
  use Agent

  defp rotate [head | tail] do
    tail ++ [head]
  end

  @doc """
  Starts node picker.
  """
  def start_link(_opts) do
    Agent.start_link fn ->
      [node() | Node.list()]
    end
  end

  @doc """
  Gets a value from the `bucket` by `key`.
  """
  def get(node_list) do
    [head | tail] = Agent.get(node_list, fn x -> x end)
    # check if node alive
    case Node.ping head do
      :pong ->
        Agent.update(node_list, fn _ -> rotate [head | tail] end)
        head
      :pang ->
        Agent.update(node_list, fn _ -> tail end)
        Parallel.NodePicker.get(node_list)
    end
  end
end
