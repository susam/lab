val m : int = 2
val n : int = let
    val m : int = 3             (* m = 3 *)
    val n : int = m * m         (* n = 9 *)
in
    m * n                       (* 3 x 9 = 27 *)
end * m                         (* 27 x 2 = 54 *)
val _ = print ("m: " ^ Int.toString m ^ "\n")
val _ = print ("n: " ^ Int.toString n ^ "\n")

val a : int = let
    val b : int = 10
in
    b * b
end
val _ = print ("a: " ^ Int.toString a ^ "\n")

(* smlnj: Error: unbound variable or constructor: b *)
(* mlton: Undefined variable: b. *)
(* val _ = print ("b: " ^ Int.toString b ^ "\n") *)
