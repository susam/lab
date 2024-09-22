val pair : int * int = (2, 3)
val _ = print ("#1 pair: " ^ Int.toString (#1 pair) ^ "\n")
val _ = print ("#2 pair: " ^ Int.toString (#2 pair) ^ "\n\n")

val triple : int * real * string = (2, 3.14, "hello")
val _ = print ("#1 triple: " ^ Int.toString (#1 triple) ^ "\n")
val _ = print ("#2 triple: " ^ Real.toString (#2 triple) ^ "\n")
val _ = print ("#3 triple: " ^ #3 triple ^ "\n\n")

val quadruple : int * int * real * real = (2, 3, 2.71, 3.14)
val _ = print ("#1 quadruple: " ^ Int.toString (#1 quadruple) ^ "\n")
val _ = print ("#2 quadruple: " ^ Int.toString (#2 quadruple) ^ "\n")
val _ = print ("#3 quadruple: " ^ Real.toString (#3 quadruple) ^ "\n")
val _ = print ("#4 quadruple: " ^ Real.toString (#4 quadruple) ^ "\n\n")

val pair_of_pairs : (int * int) * (real * real) = ((2, 3), (2.71, 3.14))
val _ = print ("#1 (#1 pair_of_pairs): " ^ Int.toString (#1 (#1 pair_of_pairs)) ^ "\n")
val _ = print ("#2 (#1 pair_of_pairs): " ^ Int.toString (#2 (#1 pair_of_pairs)) ^ "\n")
val _ = print ("#1 (#2 pair_of_pairs): " ^ Real.toString (#1 (#2 pair_of_pairs)) ^ "\n")
val _ = print ("#2 (#2 pair_of_pairs): " ^ Real.toString (#2 (#2 pair_of_pairs)) ^ "\n\n")

(* As a convenience, ML also provides a general tuple expression of
   the form (exp_1, ... , exp_n) where each exp_i is an arbitrary
   expression, not necessarily a value.  *)
val pair' : int * int = (1 + 1, 5 - 2)
val _ = print ("#1 pair': " ^ Int.toString (#1 pair') ^ "\n")
val _ = print ("#2 pair': " ^ Int.toString (#2 pair') ^ "\n\n")

(* A 0-tuple, which is also known as a null tuple, is the empty
   sequence of values, ().  It is a value of type unit, which may be
   thought of as the 0-tuple type. *)
val u : unit = ()
