# fdf
This project is about representing a landscape as a 3D object in which all surfaces are outlined in lines.

## how it works:

the program represent a model  in [isometric projection](https://en.wikipedia.org/wiki/Isometric_projection).

The coordinates of the landscape are stored in a .fdf file passed as a parameter to
the program. Here is an example:

$>cat 42.fdf

0 0 0  0  0  0  0  0  0 0 0 0  0  0  0  0  0  0 0

0 0 0  0  0  0  0  0  0 0 0 0  0  0  0  0  0  0 0

0 0 10 10 0  0  10 10 0 0 0 10 10 10 10 10 0  0 0

0 0 10 10 0  0  10 10 0 0 0 0  0  0  0  10 10 0 0

0 0 10 10 0  0  10 10 0 0 0 0  0  0  0  10 10 0 0

0 0 10 10 10 10 10 10 0 0 0 0  10 10 10 10 0  0 0

0 0 0  10 10 10 10 10 0 0 0 10 10 0  0  0  0  0 0

0 0 0  0  0  0  10 10 0 0 0 10 10 0  0  0  0  0 0

0 0 0  0  0  0  10 10 0 0 0 10 10 10 10 10 10 0 0

0 0 0  0  0  0  0  0  0 0 0 0  0  0  0  0  0  0 0

0 0 0  0  0  0  0  0  0 0 0 0  0  0  0  0  0  0 0

$>

Each number represents a point in space:

• The horizontal position corresponds to its axis.

• The vertical position corresponds to its ordinate.

• The value corresponds to its altitude.

Executing your fdf program using the example file 42.fdf:

$>./fdf 42.fdf

Should render a landscape represinting it.

### note:

>this program working only on macos system as it's using the minilibx graphics library which is based on the X server \(cocoa for our case\), I'll work on make in it crossover later..
