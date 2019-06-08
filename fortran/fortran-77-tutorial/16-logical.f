      program logical

      logical a, b

      write (*,*) 1 .lt. 2
      write (*,*) 2 .le. 2
      write (*,*) 2 .gt. 1
      write (*,*) 2 .ge. 2
      write (*,*) 1 .eq. 1
      write (*,*) 1 .ne. 2

      a = .true.
      b = a .and. 3 .lt. 5/2
      write (*,*) b

      stop
      end
