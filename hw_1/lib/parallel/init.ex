defmodule Parallel.Init do
  use Application
  
  def start(_type, _args) do
    Task.Supervisor.start_link(name: Parallel)
  end
end
