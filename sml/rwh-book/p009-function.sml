val a : real = Math.sqrt (Math.sqrt 4.0)
val _ = print ("a: " ^ Real.toString a ^ "\n")

(* smlnj: Error: operator and operand do not agree [tycon mismatch] *)
(* mlton: Function applied to incorrect argument. *)
(* val a : real = Math.sqrt Math.sqrt 4.0 *)

val b : real = (fn x : real => Math.sqrt (Math.sqrt x)) 9.0
val _ = print ("b: " ^ Real.toString b ^ "\n")

val fourthroot : real -> real = fn x : real => Math.sqrt (Math.sqrt x)
val _ = print ("fourthroot 25: " ^ Real.toString (fourthroot 25.0) ^ "\n")

fun fourthroot' (x : real) : real = Math.sqrt (Math.sqrt x)
val _ = print ("fourthroot' 25: " ^ Real.toString (fourthroot' 25.0) ^ "\n")

(* fn example without type declarations *)
val fourthroot'1 = fn x  => Math.sqrt (Math.sqrt x)
val _ = print ("fourthroot'1 25: " ^ Real.toString (fourthroot'1 25.0) ^ "\n")

(* fun example without type declarations *)
fun fourthroot'2 (x) = Math.sqrt (Math.sqrt x)
val _ = print ("fourthroot'2 25: " ^ Real.toString (fourthroot'2 25.0) ^ "\n")

fun srev (s : string) : string = implode (rev (explode s))
fun pal (s : string) : string = s ^ (srev s)
fun double (n : int) : int = n + n
fun square (n : int) : int = n * n
fun halve (n : int) : int = n div 2
fun is_even (n : int) : bool = (n mod 2 = 0)

val _ = print ("srev \"unix\": " ^ srev "unix" ^ "\n")
val _ = print ("pal \"ot\": " ^ pal "ot" ^ "\n")
val _ = print ("double 10: " ^ Int.toString (double 10) ^ "\n")
val _ = print ("square 10: " ^ Int.toString (square 10) ^ "\n")
val _ = print ("halve 10: " ^ Int.toString (halve 10) ^ "\n")
val _ = print ("is_even 10: " ^ Bool.toString (is_even 10) ^ "\n")
