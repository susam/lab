package main

import (
	"fmt"
)

func main() {
	a, b := 1, 2
	fmt.Println("a:", a, "; b:", b)

	a, b = b, a
	fmt.Println("a:", a, "; b:", b)

	_, c := 3, 4
	fmt.Println("c:", c)

	// cannot use _ as value
	// fmt.Println(_)

	f()
	_ = f()
	_ = 8.2
	_ = "foo"
}

func f() int {
	fmt.Println("f()")
	return 5
}
