package main

import (
	"fmt"
)

func main() {
	if a := 10; a > 5 {
		fmt.Println("true; a:", a)
	} else {
		fmt.Println("false; a:", a)
	}

	if a := 1; a > 5 {
		fmt.Println("true; a:", a)
	} else {
		fmt.Println("false; a:", a)
	}

	// undefined: a
	// fmt.Println("a:", a)

	var b int = 2
	fmt.Println("b:", b) // b: 2

	if b := 10; b > 5 {
		fmt.Println("true; b:", b) // b: 10
	} else {
		fmt.Println("false; b:", b)
	}

	fmt.Println("b:", b) // b: 2

	var c int = 3
	fmt.Println("c:", c) // c: 3

	if c = 10; c > 5 {
		fmt.Println("true; c:", c) // c: 10
	} else {
		fmt.Println("false; c:", c)
	}
	fmt.Println("c:", c) // c: 10

	if d, e := 1, 2; d+e == 3 {
		fmt.Println("true; d+e:", d+e)
	} else {
		fmt.Println("false; d+e:", d+e)
	}
}
