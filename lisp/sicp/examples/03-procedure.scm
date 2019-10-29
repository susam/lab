(define (square x) (* x x))
(display (square 21))
(newline)

(define (sum-of-squares x y)
  (+ (square x) (square y)))
(display (sum-of-squares 3 4))
(newline)
