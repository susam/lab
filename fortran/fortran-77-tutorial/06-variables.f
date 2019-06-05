      program varprogram

      real foobar1
      real foobar2

c Error: Syntax error in data declaration at (1)
c     real foobar@

c You should note that you cannot have a variable with the same name as
c the program. 
c
c Error: Symbol 'varprogram' at (1) cannot have a type
c     real varprogram

      real real

      foobar1= 10
      foobar2 = 20
      real = 30

      write (*,*) foobar1, foobar2, real

      stop
      end
