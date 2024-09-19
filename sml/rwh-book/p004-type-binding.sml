type float = real
val a = 2.1 : float
val b = a : real
val _ = print ("a: " ^ Real.toString a ^ "\n")
val _ = print ("b: " ^ Real.toString b ^ "\n")

(* smlnj: Error: unbound structure: Float in path Float.toString *)
(* mlton: Undefined structure: Float. *)
(* val _ = print ("a: " ^ Float.toString a ^ "\n") *)

type count = int and average = real
val c = 20 : count
val d = 4.1 : average
val _ = print ("c: " ^ Int.toString c ^ "; d: " ^ Real.toString d ^ "\n")

(* smlnj: Error: unbound type constructor: floating *)
(* mlton: Undefined type: floating. *)
(* type floating = real and averaging = floating *)

type floating = real
type averaging = floating
val e = 1.1 : floating
val f = 2.2 : averaging
val _ = print ("e: " ^ Real.toString e ^ "; f: " ^ Real.toString f ^ "\n")

type floating = int
val g = 10 : int
val _ = print ("g: " ^ Int.toString g ^ "\n")

(* smlnj: Error: expression does not match constraint [tycon mismatch] *)
(* mlton: Expression and constraint disagree. *)
(* val h = 10.0 : floating *)
