defmodule LinearAlgebra do
  @on_load :load_nifs

  def load_nifs do
    :erlang.load_nif('priv/linalg_nif', 0)
  end

  def hello do
    raise "NIF not implemented"
  end
end
