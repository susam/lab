      program types

      integer a
      real b
      double precision d
      complex c
      logical e
      character f

c List of variables in a declaration.

      integer x, y, z

      a = 10
      b = 20.0
      d = 30.0
      c = (2, 3)
      e = .TRUE.
      f = 'f'
      write (*,*) a, b, d, c, e, f

      x = 10
      y = 20
      z = 30
      write (*,*) x, y, z

c If a variable is undeclared, Fortran 77 uses a set of implicit rules
c to establish the type. This means all variables starting with the
c letters i-n are integers and all others are real.

      i = 10
      j = 20
      m = 30
      n = 40
      write (*,*) i, j, m, n

      g = 10
      h = 20
      o = 30
      p = 40
      write (*,*) g, h, o, p

      stop
      end