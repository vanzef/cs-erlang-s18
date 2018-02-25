defmodule SteganographyTest do
  use ExUnit.Case
  doctest Steganography

  test "greets the world" do
    assert Steganography.hello() == :world
  end
end
