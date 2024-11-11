package main

import (
	"fmt"
)

type FuncAB func(a int, b int) int

// It is okay to omit parameter names.
type FuncII func(int, int) int

func invokeFuncAB(f FuncAB, a int, b int) int {
	return f(a, b)
}

func invokeFuncII(f FuncII, a int, b int) int {
	return f(a, b)
}

func callFuncAB(f func(a int, b int) int, a int, b int) int {
	return f(a, b)
}

// It is okay to omit parameter names in func type.
func callFuncII(f func(int, int) int, a int, b int) int {
	return f(a, b)
}

func main() {
	a := invokeFuncAB(func(a int, b int) int {
		return a + b
	}, 10, 20)
	fmt.Println("a:", a)

	a = invokeFuncII(func(a int, b int) int {
		return a + b
	}, 10, 20)
	fmt.Println("a:", a)

	a = callFuncII(func(a int, b int) int {
		return a * b
	}, 10, 20)
	fmt.Println("a:", a)

	a = callFuncAB(func(a int, b int) int {
		return a * b
	}, 10, 20)
	fmt.Println("a:", a)
}
