defmodule RowsTest do
  use ExUnit.Case
  import LinearAlgebra

  test "rows" do
    m1 = matrix([1.0,2.0,3.0,4.0,5.0,6.0], 3, 2)
    m2 = matrix([7.0, 8.0, 9.0, 10.0],     2, 2)
    assert [25.0, 28.0, 57.0, 64.0, 89.0, 100.0] == to_array(mult(m1, m2))
  end
end

