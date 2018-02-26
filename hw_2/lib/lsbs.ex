defmodule Steganography do
  def encode(file_name, string) do
    import Binary, only: [bin_to_int: 1, int_to_bin: 2, one_to_four: 2]
    import Integer, only: [floor_div: 2]
    import BMP, only: [get_bmp: 1, drop_padding: 3, add_padding: 3,
                       get_compression: 1, rle_decompress: 3
                      ]
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
    number_of_bytes_to_encode = Integer.floor_div(bytes_in_row * rows, 4) - 16
    {:ok, good_string} = Unicode.take_safely(string, number_of_bytes_to_encode)
    good_string = int_to_bin(byte_size(good_string), 4) <> good_string

    compression = get_compression(dib_hdr)

    no_padding = case compression do
                   :comp_none -> drop_padding(image, pixel_bytes, padding_bytes)
                   :rle_8bit -> rle_decompress(pixel_bytes, 0, image)
                 end

    consume = case compression do
                :conm_none ->
                  fn consume -> fn
                      {<<h1 :: binary-size(4)>> <> r1, <<h2>> <> r2} ->
                        one_to_four(h2, h1) <> consume.({r1, r2})
                      {tail, <<>>} -> tail
                      {<<>>, _}    -> :error
                    end
                  end
                :rle_8bit -> fn consume -> fn
                      {<<h1 :: binary-size(8)>> <> r1, <<h2>> <> r2} ->
                        one_to_eight(h2, h1) <> consume.({r1, r2})
                      {tail, <<>>} -> tail
                      {<<>>, _}    -> :error
                    end
                  end
              end

    pre_encoded = Recursion.fix(consume).({no_padding, good_string})
    encoded = add_padding(pre_encoded, pixel_bytes, padding_bytes)

    # return bmp with encoded message
    {:ok, out} = File.open("encoded-" <> file_name, [:write])
    IO.binwrite(out, raw_hdrs <> encoded <> reminder)
  end

  def decode(file_name) do
    import Binary, only: [bin_to_int: 1, four_to_one: 1]
    import Integer, only: [floor_div: 2]
    import BMP, only: [get_bmp: 1, drop_padding: 3]

    {{_, _, dib_hdr}, image, _} = get_bmp(file_name)
    {:ok, h} = Map.fetch(dib_hdr, :width)
    {:ok, b} = Map.fetch(dib_hdr, :bitness)
    bitness = bin_to_int(b)
    pixels = bin_to_int(h)
    pixel_bytes = floor_div(pixels * bitness, 8) # number of pixel bytes in a row
    bytes_in_row = floor_div(pixels * bitness + 31, 32) * 4 # total bytes in a row
    padding_bytes = bytes_in_row - pixel_bytes

    no_padding = drop_padding(image, pixel_bytes, padding_bytes)
    <<a :: binary-size(4),
      b :: binary-size(4),
      c :: binary-size(4),
      d :: binary-size(4)>> <> body = no_padding

    msg_length = bin_to_int(
      <<four_to_one(a),
      four_to_one(b),
      four_to_one(c),
      four_to_one(d)>>
    )

    require IEx
    
    read = fn read -> fn
        {_, 0} -> <<>>
        {<<enc_byte :: binary-size(4)>> <> tail, counter} ->
          <<four_to_one(enc_byte)>> <> read.({tail, counter - 1})
        {<<>>, _} -> {:error, "length is too big"}
      end
    end
    
    Recursion.fix(read).({body, msg_length})
  end
end
