# Mandelbrot Set

A simple C project that generates images of the Mandelbrot Set. It can also create a sequence of images by changing the center, zoom level, and rotation.

## Features

- Generate Mandelbrot Set images.
- Save images in BMP format.
- Zoom in and out.
- Move the center of the view.
- Rotate the image.
- Combine zoom and rotation.
- Control the process using a configuration file.

## Project Files

- `main.c` — The main program.
- `mandelbrotset.h` — Mandelbrot calculations and image updates.
- `image_utils.h` — Bitmap image creation and file writing.
- `defs.h` — Data structures and command definitions.
- `utils.h` — Configuration file reading and utility functions.
- `play.cfg` — An example configuration file.
- `audio.rb` — A separate Sonic Pi script for audio.
- `.gitignore` — Files and folders excluded from Git.

## Requirements

- A C compiler, such as GCC.
- The math library used by C.

## How to Compile and Run

If GCC is installed, open a terminal in the project directory and compile the program:

```bash
gcc main.c -o mandelbrot -lm
```

Then run it with the configuration file:

```bash
./mandelbrot play.cfg
```

On Windows, if you use GCC through MinGW, run the compiled program with:

```bash
mandelbrot.exe play.cfg
```

## Configuration File

The program reads its settings and commands from a configuration file.

The first line defines the image dimensions, and the second line defines the initial coordinate boundaries.

The remaining lines contain commands that control the generated images.

Supported commands:

| Command | Description |
|---|---|
| `center` | Move the center of the view. |
| `zoom` | Change the zoom level. |
| `rotate` | Rotate the view. |
| `hold` | Repeat the current image for several frames. |
| `zoomrotate` | Change zoom and rotation together. |

For example:

```text
800*600
-2,2,-1.5,1.5
hold 5
zoom 2:30
rotate 90:20
```

The numbers after the commands control how many frames are generated for each operation.

## Output

The program saves the generated images as numbered BMP files in the current working directory, for example:

```text
00000.bmp
00001.bmp
00002.bmp
```

These images can be viewed individually or used to create an animation.

## 🎓 Academic Information

- **Course:** Basic Programming
- **Academic Level:** Bachelor's Degree — First Semester
- **Project Type:** Course Project
- **Instructor:** Dr. Sauleh Eetemadi
- **Project Date:** ‎June ‎2025
