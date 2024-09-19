type float = real
val pi : float = 3.14
val x : float = Math.sin pi
val y : float = Math.cos x

val _ = print ("pi: " ^ Real.toString pi ^ "\n")
val _ = print ("x: " ^ Real.toString x ^ "\n")
val _ = print ("y: " ^ Real.toString y ^ "\n")
