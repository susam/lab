package main

import (
	"fmt"
)

func main() {
	f()

	a := g()
	fmt.Println("a:", a)

	b, c := h()
	fmt.Println("b:", b, "; c:", c)

	f1(4, 5, "foo")

	// cannot use "foo" (type string) as type int in argument to f1
	// cannot use 5 (type int) as type string in argument to f1
	// f1(4, "foo", 5)

	f2(4, 5, "foo")
}

func f() {
	fmt.Println("f()")
}

func g() int {
	return 1
}

func h() (int, int) {
	return 2, 3
}

func f1(a int, b int, c string) {
	fmt.Println("f1(): a:", a, "; b:", b, "; c:", c)
}

func f2(a, b int, c string) {
	fmt.Println("f2(): a:", a, "; b:", b, "; c:", c)
}
