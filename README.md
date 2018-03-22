-----------------------------------------------------------
  Heat++ (ver. 0.0.1): FEM heat conduction solver
-----------------------------------------------------------

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
