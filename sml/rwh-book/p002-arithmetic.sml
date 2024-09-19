val a = 10
val b = 3 + 4
val c = 10 div 3
val d = 4 mod 3

(* smlnj: uncaught exception Div [divide by zero] *)
(* mlton: unhandled exception: Div *)
(* val dz = 4 div 0 *)

val _ = print ("a: " ^ Int.toString a ^ "\n")
val _ = print ("b: " ^ Int.toString b ^ "\n")
val _ = print ("c: " ^ Int.toString c ^ "\n")
val _ = print ("d: " ^ Int.toString d ^ "\n")
val _ = print "\n"

val _ = print ("5 div 3: " ^ Int.toString (5 div 3) ^ "\n")
val _ = print ("~5 div 3: " ^ Int.toString (~5 div 3) ^ "\n")
val _ = print ("5 mod 3: " ^ Int.toString (5 mod 3) ^ "\n")
val _ = print ("~5 mod 3: " ^ Int.toString (~5 mod 3) ^ "\n")
val _ = print ("5.0 / 3.0: " ^ Real.toString (5.0 / 3.0) ^ "\n")
val _ = print "\n"

val e = 4 mod 3 : int
val _ = print ("e: " ^ Int.toString e ^ "\n")

val f = 5.0 / 3.0 : real
val _ = print ("f: " ^ Real.toString f ^ "\n")

(* smlnj: Error: expression does not match constraint [tycon mismatch] *)
(* mlton: Expression and constraint disagree. *)
(* val g = 5.0 / 3.0 : int *)
