-----------------------------------------------------------
  Heat++ (ver. 0.0.1): FEM heat conduction solver
-----------------------------------------------------------

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

---------------------------------------------------
  Heat++ Installation
---------------------------------------------------

To build **Heat++** run `make` from the root directory of the source distribution.
In order to be able to run **Heat++** from the command line you should include the
folder "/path/to/Heat++/bin" to your $PATH environment variable.
