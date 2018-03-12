defmodule RowsTest do
  use ExUnit.Case

  test "rows" do
    mat = LinearAlgebra.matrix(2,3)
    assert 2 == LinearAlgebra.rows(mat)

    mat = LinearAlgebra.matrix(99,3)
    assert 99 == LinearAlgebra.rows(mat)
    
    assert :err == LinearAlgebra.matrix(1,0)
    assert :err == LinearAlgebra.matrix(0,1)
  end
end

