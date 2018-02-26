defmodule BMP do
  # import List, only: [foldr: 3]
  import Enum, only: [map: 2, into: 2]
  
  def read_bmp_header(file) do
    [
      {:signature,   2},
      {:file_size,   4},
      {:reserved_1,  2},
      {:reserved_2,  2},
      {:file_offset, 4}
    ]
    |> map(fn({atom, bytes}) -> {atom, IO.binread(file, bytes)} end)
    |> into(%{})
  end

  def read_dib_header(file) do
    [
      {:dib_hdr_size,     4, :infohdr}, # the size of this header
      {:width,            4, :infohdr}, # the bitmap width in pixels (signed integer)
      {:height,           4, :infohdr}, # the bitmap height in pixels (signed integer)
      {:color_planes,     2, :infohdr}, # the number of color planes (must be 1)
      {:bitness,          2, :infohdr}, # the number of bits per pixel
      {:compression,      4, :infohdr}, # the compression method being used
      {:image_size,       4, :infohdr}, # the image size
      {:hor_resol,        4, :infohdr}, # the horizontal resolution of the image
      {:vert_resol,       4, :infohdr}, # the vertical resolution of the image
      {:palette_colors,   4, :infohdr}, # the number of colors in the color palette
      {:important_colors, 4, :infohdr}, # the number of important colors used
      # {:red_channel,      4, :v5hdr},
      # {:green_channel,    4, :v5hdr},
      # {:blue_channel,     4, :v5hdr},
      # {:alpha_channel,    4, :v5hdr},
      # {:color_space_type, 4, :v5hdr},
      # {:color_space_endp, 4, :v5hdr},
      # {:red_gamma,        4, :v5hdr},
      # {:green_gamma,      4, :v5hdr},
      # {:blue_gamma,       4, :v5hdr},
      # {:intent,           4, :v5hdr},
      # {:icc_profile_data, 4, :v5hdr},
      # {:icc_profile_size, 4, :v5hdr},
      # {:reserved_dib,     4, :v5hdr}
    ]
    |> map(fn({atom, bytes, _}) -> {atom, IO.binread(file, bytes)} end)
    |> into(%{})
  end

  # def read_color_table(file, dib_header) do
  #   {:ok, number_of_colors} = fetch(dib_header, :palette_colors)
  #   IO.binread(file, 4*Binary.bin_to_int(number_of_colors))
  # end
  
  def get_compression(dib_header) do
    case Map.fetch(dib_header, :compression) do
      {:ok, <<0, 0, 0, 0>>} -> :comp_none
      {:ok, <<1, 0, 0, 0>>} -> :rle_8bit
      _                     -> :unsupported
    end
  end

  def get_image_array(file, bmp_header, dib_header) do
    {:ok, to_skip}  = Map.fetch(bmp_header, :file_offset)
    to_skip         = Binary.bin_to_int(to_skip)
    {:ok, img_size} = Map.fetch(dib_header, :image_size)
    img_size        = Binary.bin_to_int(img_size)
    before_image    = IO.binread(file, to_skip)
    image           = IO.binread(file, img_size)
    after_image     = IO.binread(file, :all)
    {before_image, image, after_image}
  end

  def get_bmp(file_name) do
    {:ok, file} = File.open(file_name, [:read])
    bmp_header  = read_bmp_header(file)
    dib_header  = read_dib_header(file)
    File.close(file)
    {:ok, file} = File.open(file_name, [:read])
    {raw_headers, image, reminder} = get_image_array(file, bmp_header, dib_header)
    File.close(file)
    {{raw_headers, bmp_header, dib_header}, image, reminder}
  end

  def drop_padding(<<>>, _, _) do <<>> end
  def drop_padding(array, pixel_bytes, padding_bytes) do
    <<pixels :: binary-size(pixel_bytes),
      _ :: binary-size(padding_bytes)>> <> tail = array
    pixels <> drop_padding(tail, pixel_bytes, padding_bytes)
  end
  
  def add_padding(<<>>, _, _) do <<>> end
  def add_padding(array, pixel_bytes, padding_bytes) do
    <<pixels :: binary-size(pixel_bytes)>> <> tail = array
    pixels
      <> Binary.replicate_byte(0, padding_bytes)
      <> add_padding(tail, pixel_bytes, padding_bytes)
  end

  def rle_decompress(_, _, <<>>) do <<>> end
  def rle_decompress(bytes_in_row, counter, <<0, code>> <> rest) do
    import Binary, only: [replicate_byte: 2, split_at: 2]
    case code do
      0 -> # eol
        replicate_byte(0, bytes_in_row - counter) <>
          rle_decompress(bytes_in_row, 0, rest)
      1 -> # eof
        <<>>
      2 -> # delta
        {<<hor, ver>>, rest} = split_at(rest, 2)
        replicate_byte(0, bytes_in_row - counter) <>
          replicate_byte(0, ver * bytes_in_row) <>
          replicate_byte(0, counter + hor) <>
          rle_decompress(bytes_in_row, counter + hor, rest)      
      _ ->
        {write, rest} = split_at(rest, code)
        write <> rle_decompress(bytes_in_row, counter + code, rest)        
    end
  end
  def rle_decompress(bytes_in_row, counter, <<number, color>> <> rest) do
    import Binary, only: [replicate_byte: 2]
    replicate_byte(color, number) <>
      rle_decompress(bytes_in_row, counter + number, rest)
  end
end
