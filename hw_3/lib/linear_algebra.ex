defmodule LinearAlgebra do
  @on_load :load_nifs

  def load_nifs do
    :erlang.load_nif('build/linalg_nif', 0)
  end
  
  def one do
    raise "NIF not implemented: one/0"
  end

  def matrix(_, _) do
    raise "NIF not implemented: matrix/2"
  end

  def matrix(_, _, _) do
    raise "NIF not implemented: matrix/3"
  end

  def vvector(rows) do
    matrix(rows, 1)
    # raise "NIF not implemented: vvector/1"
  end

  def hvector(columns) do
    matrix(1, columns)
    # raise "NIF not implemented: hvector/1"
  end

  def rows(_) do
    raise "NIF not implemented: rows/1"
  end

  def columns(_) do
    raise "NIF not implemented: columns/1"
  end

  def to_array(_) do
    raise "NIF not implemented: to_array/1"
  end

  def sum(_,_) do
    raise "NIF not implemented: sum/2"
  end

  def mult_by_scalar(_,_) do
    raise "NIF not implemented: mult_by_scalar/2"
  end

end