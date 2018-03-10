defmodule LinearAlgebra do
  @on_load :load_nifs

  def load_nifs do
    :erlang.load_nif('build/linalg_nif', 0)
  end

  def matrix_new(rows, columns) do
    raise "NIF not implemented"
  end
end
