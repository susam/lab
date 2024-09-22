val x : real = 2.0

fun f (x : real) : real =
    x + x

fun g (y : real) : real =
    x + y

fun h (x : real) : real =
    let
        val x : real = 3.0
    in
        x + x                   (* 6 *)
    end * x                     (* 6 times x *)

val _ = print ("f 10.0: " ^ Real.toString (f 10.0) ^ "\n")
val _ = print ("g 10.0: " ^ Real.toString (g 10.0) ^ "\n")
val _ = print ("h 10.0: " ^ Real.toString (h 10.0) ^ "\n")
