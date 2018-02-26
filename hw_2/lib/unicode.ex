defmodule Unicode do
  def take_safely(string, number_of_bytes) do
    # IO.puts string
    # IO.puts number_of_bytes
    if number_of_bytes > byte_size(string) do
      {:ok, string}
    else
      <<head :: binary-size(number_of_bytes), _ :: binary>> = string
      {:ok, hd(String.chunk(head, :valid))}
    end
  end
end
