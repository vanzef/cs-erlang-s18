defmodule Parallel.Examples do
  def fac 0 do 1 end
  def fac n do n * fac(n - 1) end

  def test_fac(list) do
    Parallel.map(&fac/1, list)
  end

  def test_sleep(list) do
    Parallel.map(&sleep_and_reply/1, list)
  end

  def sleep_and_reply(seconds) do
    :timer.sleep(1000 * seconds)
    seconds
  end
end
