```
         _       _    _            _                 _
        / /\    / /\ /\ \         / /\              /\ \         _          _
       / / /   / / //  \ \       / /  \             \_\ \       /\ \       /\ \
      / /_/   / / // /\ \ \     / / /\ \            /\__ \   ___\ \_\   ___\ \_\
     / /\ \__/ / // / /\ \_\   / / /\ \ \          / /_ \ \ /___/\/_/_ /___/\/_/_
    / /\ \___\/ // /_/_ \/_/  / / /  \ \ \        / / /\ \ \\__ \/___/\\__ \/___/\
   / / /\/___/ // /____/\    / / /___/ /\ \      / / /  \/_/  /\/____\/  /\/____\/
  / / /   / / // /\____\/   / / /_____/ /\ \    / / /         \ \_\      \ \_\
 / / /   / / // / /______  / /_________/\ \ \  / / /           \/_/       \/_/
/ / /   / / // / /_______\/ / /_       __\ \_\/_/ /
\/_/    \/_/ \/__________/\_\___\     /____/_/\_\/

```

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

---------------------------------------------------
  Heat++ Installation
---------------------------------------------------

To build Heat++ run `make` from the root directory of the source distribution.
In order to be able to run Heat++ from the command line you should include the
folder "/path/to/Heat++/bin" to your $PATH environment variable.
