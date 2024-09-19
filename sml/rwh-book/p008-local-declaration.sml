local
    val a : int = 10

    val _ = print ("(1) local: a: " ^ Int.toString a ^ "\n")
in
    val b : int = a + 1

    val _ = print ("(1) in: a: " ^ Int.toString a ^ "\n")
    val _ = print ("(1) in: b: " ^ Int.toString b ^ "\n")

    local
        val c : int = b + 1

        val _ = print ("(2) local: a: " ^ Int.toString a ^ "\n")
        val _ = print ("(2) local: b: " ^ Int.toString b ^ "\n")
        val _ = print ("(2) local: c: " ^ Int.toString c ^ "\n")

    in
        val d : int = c * c

        val _ = print ("(2) in: a: " ^ Int.toString a ^ "\n")
        val _ = print ("(2) in: b: " ^ Int.toString b ^ "\n")
        val _ = print ("(2) in: c: " ^ Int.toString c ^ "\n")
        val _ = print ("(2) in: d: " ^ Int.toString d ^ "\n")
    end

    val _ = print ("(1) local: a: " ^ Int.toString a ^ "\n")
    val _ = print ("(1) local: b: " ^ Int.toString b ^ "\n")
    val _ = print ("(1) local: d: " ^ Int.toString d ^ "\n")

    (* smlnj: Error: unbound variable or constructor: c *)
    (* mlton: Undefined variable: c. *)
    (* val _ = print ("(1) in: c: " ^ Int.toString c ^ "\n") *)
end

val _ = print ("b: " ^ Int.toString b ^ "\n")
val _ = print ("d: " ^ Int.toString d ^ "\n")

(* smlnj: Error: unbound variable or constructor: a *)
(* mlton: Undefined variable: a. *)
(* val _ = print ("a: " ^ Int.toString a ^ "\n") *)

(* smlnj: Error: unbound variable or constructor: c *)
(* mlton: Undefined variable: c. *)
(* val _ = print ("c: " ^ Int.toString c ^ "\n") *)
