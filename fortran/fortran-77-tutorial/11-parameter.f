      program parameters

      real pi, e
      complex i

c Note: j is undeclared, so it is implicitly an integer.

      parameter (pi = 3.14159265, e = 2.71828)
      parameter (i = (0, 1), j = 10)

c Error: Named constant 'pi' in variable definition context (assignment) at (1)
c     pi = 3.14

      write (*,*) pi, e, i, j

      stop
      end
