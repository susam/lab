      program real

      real a
      double precision b

c
c Warning: GNU Extension: Nonstandard type declaration REAL*4 at (1)
c Warning: GNU Extension: Nonstandard type declaration REAL*8 at (1) 
c Warning: GNU Extension: Nonstandard type declaration REAL*16 at (1)

      real*4 c
      real*8 d
      real*16 e

c Error: Old-style type declaration REAL*1 not supported at (1)
c Error: Old-style type declaration REAL*2 not supported at (1)
c Error: Old-style type declaration REAL*3 not supported at (1)
c Error: Old-style type declaration REAL*12 not supported at (1)

c     real*1 f
c     real*2 f
c     real*3 f
c     real*12 f

c Error: Unclassifiable statement at (1)
c     double f

      a = 10.0
      b = 20.0
      c = 10.0
      d = 20.0
      e = 30.0

      write (*,*) a, b, c, d, e

      stop
      end
