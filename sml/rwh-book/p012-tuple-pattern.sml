val ((i : int, s : string),
     (r : real, c : char)) = ((10, "hello"), (3.14, #"a"))
val _ = print ("i: " ^ Int.toString i ^ "\n")
val _ = print ("s: " ^ s ^ "\n")
val _ = print ("r: " ^ Real.toString r ^ "\n")
val _ = print ("c: " ^ Char.toString c ^ "\n\n")

val ((i', s'), (r', c')) = ((10, "hello"), (3.14, #"a"))
val _ = print ("i': " ^ Int.toString i' ^ "\n")
val _ = print ("s': " ^ s' ^ "\n")
val _ = print ("r': " ^ Real.toString r' ^ "\n")
val _ = print ("c': " ^ Char.toString c' ^ "\n\n")

val ((_, _), (r'': real, _)) = ((10, "hello"), (3.14, #"a"))
val _ = print("r'': " ^ Real.toString r'' ^ "\n\n")

val (is : int * string, rc: real * char) = ((10, "hello"), (3.14, #"a"))
val _ = print ("#1 is: " ^ Int.toString (#1 is) ^ "\n")
val _ = print ("#2 is: " ^ #2 is ^ "\n")
val _ = print ("#1 rc: " ^ Real.toString (#1 rc) ^ "\n")
val _ = print ("#2 rc: " ^ Char.toString (#2 rc) ^ "\n")
