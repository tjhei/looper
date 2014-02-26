looper
======

Used for deal.II ParameterHandler files to create loops without changing your program.

Usage:
	looper <programname> <loopfile>

Example:
	looper ./step-34 parameters.prm

where parameters.prm can contain lists in the form:

      set refinement = {3|4|5|6}

which will run the binary with
      set refinement = 3
followed by
      set refinement = 4
etc.
 

