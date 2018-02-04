defmodule ParallelTest do
  use ExUnit.Case, async: true

  import Parallel.Examples

  # setup do
  #   {:ok, host} = :inet.gethostname()
  #   host = to_string(host)
  #   foo = String.to_atom("foo@" <> host)
  #   bar = String.to_atom("bar@" <> host)
  #   assert Node.connect foo
  #   assert Node.connect bar
  # end

  test "test factorial" do
    test_list = for _ <- 1..100, do: :rand.uniform(500)
    assert test_fac(test_list) == Enum.map(test_list, &fac/1)
  end
end
