## Heat++ (ver. 0.0.1): FEM heat conduction solver

[![Build Status](https://travis-ci.org/seraco/HeatConduction.svg?branch=master)](https://travis-ci.org/seraco/HeatConduction)

Finite element method solver for heat conduction problems on flat plates with
the following geometry:

```
                      top h = 0.5 * (a*x*x + b*x + h1)
                      ________________________________
                     |                                |
                     |                                |
                     |                                |
   h1 or left height |                                | h2 or right height
                     |                                |       
                     |                                |
                     |________________________________|
                    bottom h = -0.5 * (a*x*x + b*x + h1)
```

## Heat++ Installation

To build **Heat++** run `make` from the root directory of the source distribution.
In order to be able to run **Heat++** from the command line you should include the
folder "/path/to/Heat++/bin" to your $PATH environment variable.

## Run **Heat++**

To run **Heat++** the following parameters have to be specified:

    * -A: constant a for defining height of the plate.
    * --left-height: h1 dimension of the plate.
    * --right-height: h2 dimension of the plate.
    * -L: length of the plate, from the left to the right edge.
    * -T: thickness of the plate.
    * --k-xx: conductivity in the xx direction.
    * --k-xy: conductivity in the xy direction.
    * --k-yy: conductivity in the yy direction.
    * --n-x: number of elements in the x direction.
    * --n-y: number of elements in the y direction.
    * --flux-location: location of flux boundary condition.
    * --flux-value: value of flux boundary condition.
    * --temp-location: location of temperature boundary condition.
    * --temp-value: value of temperature boundary condition.

An example is here presented:

```
Heat++.out -A 0.0 --left-height 1.0 --right-height 1.0 -L 2.0 -T 0.2 \
           --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
           --n-x 10 --n-y 5 \
           --flux-location top --flux-value 2500.0 \
           --temp-location bottom --temp-value 10.0
```

The solution is printed in the file `disp.vtk`. This file can then be plotted.

## License

[MIT License](LICENSE)
