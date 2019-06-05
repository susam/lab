      program real

      real a
      double precision b

c
c Error: GNU Extension: Nonstandard type declaration REAL*8 at (1)
c Warning: GNU Extension: Nonstandard type declaration REAL*8 at (1) 
c
      real*8 c

      a = 10
      b = 20.0
      c = 30.0

      write (*,*) a, b, c

      stop
      end
