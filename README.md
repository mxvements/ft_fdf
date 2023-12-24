<div align="center">
    <img src="https://img.shields.io/badge/status-wip-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/badge/started-23%20%2F%2012%20%2F%202023-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/badge/score-1--%20%2F%20100-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/github/languages/top/mxvements/ft_fdf?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/github/last-commit/mxvements/ft_fdf?color=00ABAD&style=flat-square" />
    <br>
    <a href='https://www.linkedin.com/in/luciami' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=1323233&color=323233'/></a>
    <a href='https://profile.intra.42.fr/users/luciama2' target="_blank"><img alt='42' src='https://img.shields.io/badge/Madrid-100000?style=flat-square&logo=42&logoColor=white&labelColor=323233&color=323233'/></a>
    <br>
</div>

# ft_fdf

The representation in 3D of a landscape is a critical aspect of modern mapping. For example, in these times of spatial exploration, to have a 3D representation of Mars is a prerequisite condition to its conquest. As another example, comparing various 3D representations of an area of high tectonic activity will allow you to better understand these phenomena and their evolution, and as a result, be better prepared. It’s your turn today to modelize some 3D magnificent landscapes, imaginary or not.

# Mandatory part

| **Program Name** | fdf |
| ---------------- | --- |
| **Turn in files** | Makefile, *.h, *.c |
| **Makefile** | Name, all, clean, fclean, re |
| **Arguments** | A file in format *.fdf |
| **External functs** | + open, close, read, write, malloc, free, perror, strerror, exit. + All functions of the math library (-lm compiler option man man 3 math). * All functions of the MiniLibX. + ft_printf and any equivalent YOU coded |
| **Libft auth** | Yes |
| **Description** | This project is about creating a simple wireframe model of a landscape |

This project is about creating a simple wireframe model representation of a 3D landscape by linking various points (x, y, z) thanks to line segments (edges). Your project must comply with the following rules:

+ You must use the MiniLibX. Either the version available on the school machines, or installing it using its sources.
+ You have to turn in a Makefile which will compile your source files. It must not relink.
+ Global variables are forbidden.

## Rendering

Your program has to represent the model in isometric projection. The coordinates of the landscape are stored in a .fdf file passed as a parameter to
your program. Here is an example:

```txt
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 10 10 0 0 10 10 0 0 0 10 10 10 10 10 0 0 0
0 0 10 10 0 0 10 10 0 0 0 0 0 0 0 10 10 0 0
0 0 10 10 0 0 10 10 0 0 0 0 0 0 0 10 10 0 0
0 0 10 10 10 10 10 10 0 0 0 0 10 10 10 10 0 0 0
0 0 0 10 10 10 10 10 0 0 0 10 10 0 0 0 0 0 0
0 0 0 0 0 0 10 10 0 0 0 10 10 0 0 0 0 0 0
0 0 0 0 0 0 10 10 0 0 0 10 10 10 10 10 10 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

Each number represents a point in space:

+ The horizontal position corresponds to its axis.
+ The vertical position corresponds to its ordinate.
+ The value corresponds to its altitude.

Executing your fdf program using the example file 42.fdf

```sh
./fdf 42.fdf
```

## Graphic management

+ Your program has to display the image in a window.
+ The management of your window must remain smooth (changing to another window, minimizing, and so forth).
+ Pressing ESC must close the window and quit the program in a clean way.
+ Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
+ The use of the images of the MiniLibX is mandatory.

# Bonus part

Usually, you would be encouraged to develop your own original extra features. However, there will be much more interesting graphic projects later. They are waiting for you!! Don’t lose too much time on this assignment!

You are allowed to use other functions to complete the bonus part as long as their use is justified during your evaluation. Be smart!

You will get some extra points if you can:

+ Include one extra projection (such as parallel or conic)!
+ Zoom in and out.
+ Translate your model.
+ Rotate your model.
+ Add one more bonus of your choice

# How to use

*tbd*

# Other

## Norminete

At 42 School, it is expected that almost every project is written in accordance with the Norm, which is the coding standard of the school.

<a href="https://github.com/42School/norminette">
<a>Norminette's repository</a>

```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be a maximum of 25 lines, not counting the function's curly brackets
- Each line must be at most 80 columns wide, comments included
- A function can take 4 named parameters maximum
- No assigns and declarations in the same line (unless static or const)
- You can't declare more than 5 variables per function
- ...
```
## Aknowledgments

+ [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html)

# License
[MIT License](https://github.com/mxvements/ft_license/blob/main/LICENSE.txt)
