defmodule Binary do
  use Bitwise
  def bin_to_int(bin) do
    import List, only: [foldr: 3]
    foldr(:binary.bin_to_list(bin), 0, fn(x, acc) -> (acc <<< 8) + x end)
  end

  def int_to_bin(_, 0) do <<>> end
  def int_to_bin(int, width) do
    <<int>> <> int_to_bin(int >>> 8, width - 1)
  end

  def one_to_four(byte, <<a, b, c, d>>) do
    <<(a ||| 3) &&& (252 ||| (byte >>> 6)),
      (b ||| 3) &&& (252 ||| (byte >>> 4)),
      (c ||| 3) &&& (252 ||| (byte >>> 2)),
      (d ||| 3) &&& (252 ||| (byte >>> 0))>>
  end

  def four_to_one(<<a, b, c, d>>) do
    ((a &&& 3) <<< 6)
      ||| ((b &&& 3) <<< 4)
      ||| ((c &&& 3) <<< 2)
      |||  (d &&& 3)
  end

  def one_to_eight(byte, <<a,b,c,d,e,f,g,h>>) do
    <<(a ||| 1) &&& (7 ||| (byte >>> 7)),
      (b ||| 1) &&& (7 ||| (byte >>> 6)),
      (c ||| 1) &&& (7 ||| (byte >>> 5)),
      (d ||| 1) &&& (7 ||| (byte >>> 4)),
      (e ||| 1) &&& (7 ||| (byte >>> 3)),
      (f ||| 1) &&& (7 ||| (byte >>> 2)),
      (g ||| 1) &&& (7 ||| (byte >>> 1)),
      (h ||| 1) &&& (7 ||| (byte >>> 0))>>
  end

  def one_to_eight(<<a,b,c,d,e,f,g,h>>) do
    <<((a &&& 1) <<< 7) |||,
      ((b &&& 1) <<< 6) |||,
      ((c &&& 1) <<< 5) |||,
      ((d &&& 1) <<< 4) |||,
      ((e &&& 1) <<< 3) |||,
      ((f &&& 1) <<< 2) |||,
      ((g &&& 1) <<< 1) |||,
      ((h &&& 1) <<< 0)>>
  end

  def replicate_byte(_, 0) do <<>> end
  def replicate_byte(byte, n) do <<byte>> <> replicate_byte(byte, n - 1) end

  def take_n_bytes(_, 0) do <<>> end
  def take_n_bytes(<<>>, _) do {:error, "not enough bytes in array"} end
  def take_n_bytes(<<byte>> <> array, n) do
    <<byte>> <> take_n_bytes(array, n - 1)
  end

  defp split_at_inner({left, right}, 0) do {left, right} end
  defp split_at_inner({left, <<>>}, _) do {left, <<>>} end
  defp split_at_inner({left, <<byte>> <> right}, n) do
    split_at_inner({left <> <<byte>>, right}, n - 1)    
  end

  def split_at(array, n) do split_at_inner({array, <<>>}, n) end
end
