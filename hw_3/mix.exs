defmodule LinearAlgebra.MixProject do
  use Mix.Project

  def project do
    [
      app: :linear_algebra,
      version: "0.1.0",
      elixir: "~> 1.6",
      start_permanent: Mix.env() == :prod,
      compilers: [:make, :elixir, :app],
      aliases: aliases(),
      deps: deps()
    ]
  end

  defp aliases do
    [clean: ["clean", "clean.make"]]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      # {:dep_from_hexpm, "~> 0.3.0"},
      # {:dep_from_git, git: "https://github.com/elixir-lang/my_dep.git", tag: "0.1.0"},
    ]
  end

end

defmodule Mix.Tasks.Compile.Make do
  def run(_) do
    {result, _error_code} = System.cmd("make", [], stderr_to_stdout: true)
    Mix.shell.info result
    :ok
  end
end

defmodule Mix.Tasks.Clean.Make do
  def run(_) do
    {result, _error_code} = System.cmd("make", ["clean"], stderr_to_stdout: true)
    Mix.shell.info result
    :ok
  end
end
