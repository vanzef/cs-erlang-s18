defmodule Binary do
  def bin_to_int(bin) do
    use Bitwise
    import List, only: [foldr: 3]
    foldr(:binary.bin_to_list(bin), 0, fn(x, acc) -> (acc <<< 8) + x end)
  end

  def one_to_four(byte, <<a, b, c, d>>) do
    use Bitwise
    <<(a ||| 3) &&& (252 ||| (byte >>> 6)),
      (b ||| 3) &&& (252 ||| (byte >>> 4)),
      (c ||| 3) &&& (252 ||| (byte >>> 2)),
      (d ||| 3) &&& (252 ||| (byte >>> 0))>>
  end

  def replicate_byte(_, 0) do <<>> end
  def replicate_byte(byte, n) do <<byte>> <> replicate_byte(byte, n - 1) end
end
