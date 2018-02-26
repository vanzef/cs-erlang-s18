defmodule Steganography do
  @moduledoc """
  Documentation for Steganography.
  """

  @doc """
  Hello world.

  ## Examples

      iex> Steganography.hello
      :world

  """
  def encode(file_name, string) do
    import Binary, only: [bin_to_int: 1, one_to_four: 2]
    import Integer, only: [floor_div: 2]
    import BMP, only: [get_bmp: 1, drop_padding: 3, add_padding: 3]

    {{raw_hdrs, _, dib_hdr}, image, reminder} = get_bmp(file_name)
    {:ok, v} = Map.fetch(dib_hdr, :height)
    {:ok, h} = Map.fetch(dib_hdr, :width)
    {:ok, b} = Map.fetch(dib_hdr, :bitness)
    bitness = bin_to_int(b)
    rows = bin_to_int(v)                  # total number of rows
    pixels = bin_to_int(h)
    pixel_bytes = floor_div(pixels * bitness, 8) # number of pixel bytes in a row
    bytes_in_row = floor_div(pixels * bitness + 31, 32) * 4 # total bytes in a row
    padding_bytes = bytes_in_row - pixel_bytes
    number_of_bytes_to_encode = Integer.floor_div(bytes_in_row * rows, 4)
    {:ok, good_string} = Unicode.take_safely(string, number_of_bytes_to_encode)

    no_padding = drop_padding(image, pixel_bytes, padding_bytes)

    consume = fn consume -> fn
        {<<h1 :: binary-size(4)>> <> r1, <<h2>> <> r2} ->
          one_to_four(h2, h1) <> consume.({r1, r2})
        {tail, <<>>} -> tail
        {<<>>, _}    -> :error
      end
    end

    pre_encoded = Recursion.fix(consume).({no_padding, good_string})
    encoded = add_padding(pre_encoded, pixel_bytes, padding_bytes)

    # return bmp with encoded message
    {:ok, out} = File.open("encoded-" <> file_name, [:write])
    IO.binwrite(out, raw_hdrs <> encoded <> reminder)
  end
end
