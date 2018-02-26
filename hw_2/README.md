# Steganography

## Usage

Run `iex -S mix` to enter interactive shell.

To encode use `Steganography.encode(file_name, string)`, to decode --- `Steganography.decode(file_name)`.

### Example: Kitty

Test image:

![](./media/kitty_small.bmp)

Test text:
```
The domestic cat (Felis silvestris catus or Felis catus) is a small, typically furry, carnivorous mammal. They are often called house cats when kept as indoor pets or simply cats when there is no need to distinguish them from other felids and felines. They are often valued by humans for companionship and for their ability to hunt vermin. There are more than seventy cat breeds recognized by various cat registries.

Cats are similar in anatomy to the other felids, with a strong flexible body, quick reflexes, sharp retractable claws, and teeth adapted to killing small prey. Cat senses fit a crepuscular and predatory ecological niche. Cats can hear sounds too faint or too high in frequency for human ears, such as those made by mice and other small animals. They can see in near darkness. Like most other mammals, cats have poorer color vision and a better sense of smell than humans. Cats, despite being solitary hunters, are a social species and cat communication includes the use of a variety of vocalizations (mewing, purring, trilling, hissing, growling, and grunting), as well as cat pheromones and types of cat-specific body language.
```

Result:

![](./media/encoded-kitty_small.bmp)

Diff via `compare media/kitty_small.bmp media/encoded-kitty_small.bmp -compose src media/kitty_small_diff.png`:

![](./media/kitty_small_diff.png)

The [image of kitty ](https://en.wikipedia.org/wiki/Cat#/media/File:Kittyply_edit1.jpg) and the [text](https://en.wikipedia.org/wiki/Cat) were taken from Wikipedia. Both are licensed under CC-BY-SA license.

### Example 2: Haiku

**Disclaimer: all images in this example are scaled for better visibility**

Test image:

![](./media/test_scaled.bmp)

Test string:
```
ながむとて花にもいたし首の骨
```
Result:

![](./media/encoded-test_scaled.bmp)

Diff via `compare media/test.bmp media/encoded-test.bmp -compose src media/test_diff.png`:

![](./media/test_diff_scaled.png)

Haiku was written by Nishiyama Sōin (西山 宗因).
