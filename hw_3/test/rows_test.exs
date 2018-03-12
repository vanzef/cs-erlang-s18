defmodule RowsTest do
  use ExUnit.Case

  test "rows" do
    mat = LinearAlgebra.matrix(2,3)
    assert 2 == LinearAlgebra.rows(mat)
  end
end

