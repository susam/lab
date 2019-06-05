      write (*,*) 'hello'
      end

c The stop statement is optional and may seem superfluous since the
c program will stop when it reaches the end anyway, but it is recommended
c to always terminate a program with the stop statement to emphasize that
c the execution flow stops there.

c The standard requires all floating point exceptions that are
c signalling to be reported when a STOP statement is executed. Thus
c omitting the STOP statement would omit warnings about such exceptions.
