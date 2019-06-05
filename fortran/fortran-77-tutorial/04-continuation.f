      program calc

      a = 1 +
     *    2

      b = 1 +
     &    2

c Any character can be used instead of the plus sign as a continuation
c character.

      c = 1 +
     a    2

c It is considered good programming style to use either the plus sign,
c an ampersand, or digits (using 2 for the second line, 3 for the third,
c and so on). 

      d = 1 +
     1    2 +
     2    3 +
     34+
     45

      write (*,*) a, b, c, d

c---5---10---15---20---25---30---35---40---45---50---55---60---65---70---75--79
      e = 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 1 + 2 + 3 + 4
c Warning: Line truncated at (1) [-Wline-truncation]

c Output is 3 (not 10)
      write (*,*) e

      f = 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 1 +
     +    2 + 3 + 4

      write (*,*) f

      stop
      end
