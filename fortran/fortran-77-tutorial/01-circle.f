      program circle
      real r, area

c This program reads a real number r and prints the area of a circle
c with radius r.

      write (*,*) 'Enter radius r:'
      read (*,*) r
      area = 3.14159 * r * r
      write (*,*) 'Area = ', area

      stop
      end
