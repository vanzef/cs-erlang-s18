defmodule Recursion do
  @moduledoc """
  Some recursion primitives.
  """

  @doc """
  Strict Y combinator.

  ## Example

      iex(1)> fac_lambda = fn fac_lambda -> fn
      ...>     0 -> 1
      ...>     n -> n * fac_lambda.(n - 1)
      ...>   end
      ...> end
      #Function<...>
      iex(2)> Recursion.fix(fac_lambda).(5)
      120

  """
  def fix(f) do
    (fn z ->
      z.(z)
    end).(fn x ->
      f.(fn y -> (x.(x)).(y) end)
    end)
  end
end
