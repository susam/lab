val i = 10 : int
val r = 3.14 : real
val c = #"a" : char
val s = "abc" : string
val b = true : bool

val _ = print ("r: " ^ Real.toString r ^ "\n")
val _ = print ("c: " ^ Char.toString c ^ "\n")
val _ = print ("s: " ^ s ^ "\n")
val _ = print ("b: " ^ Bool.toString b ^ "\n")

val _ = print ("ord c: " ^ Int.toString(ord c) ^ "\n")
val _ = print ("chr 65: " ^ Char.toString(chr 65) ^ "\n")
val _ = print ("size s: " ^ Int.toString(size s) ^ "\n")
val _ = print (if b then "b is true\n" else "b is false\n")
val _ = print (if not b then "b is false\n" else "b is true\n")

val _ = print ("real 3: " ^ Real.toString (real 3) ^ "\n")
val _ = print ("round 1.4: " ^ Int.toString (round 1.4) ^ "\n")
val _ = print ("round 1.5: " ^ Int.toString (round 1.5) ^ "\n")
val _ = print ("round 2.5: " ^ Int.toString (round 2.5) ^ "\n")

val _ = print (if 1 < 2 then "less\n" else "greater\n")
val _ = print (Int.toString (if 1 < 2 then 0 else 1 div 1) ^ "\n")

(* smlnj: Error: types of if branches do not agree [overload - bad instantiation] *)
(* mlton: Then and else branches disagree. *)
(* val _ = print (if 1 < 2 then "less\n" else 10) *)
