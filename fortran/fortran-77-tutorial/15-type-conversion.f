      program typeconversion

      real x
      real y
      double precision w

c The integer numbers are converted to real numbers.
      x = 10
      x = x + 1
      write (*,*) x

      write (*,*) int(1.0), int(1.0d0)
      write (*,*) real(2), real(2.0d0)
      write (*,*) dble(3), dble(3.0)
      write (*,*) ichar('A'), ichar('B'), ichar('C')
      write (*,*) char(65), char(66), char(67)

      x = 1.1
      y = 1.1

      w = dble(x * y)
      write (*,*) w

      w = dble(x) * dble(y)
      write (*,*) w

      stop
      end
