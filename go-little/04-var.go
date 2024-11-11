package main

import (
	"fmt"
)

func main() {
	var a int
	fmt.Println("a:", a)

	a = 1
	fmt.Println("a:", a)

	var b int = 2
	fmt.Println("b:", b)

	c := 3
	fmt.Println("c:", c)

	// no new variables on left side of :=
	// c := 4

	d := getValue()
	fmt.Println("d:", d)

	// syntax error: unexpected comma, expecting semicolon or newline or }
	// var x int, var y int = 5, 6

	var e, f int = 5, 6
	fmt.Println("e:", e, "; f:", f)

	// There must be at least one new var on left side of :=
	f, g := 7, 8.2
	fmt.Println("f:", f, "; g:", g)

	// It is an error if there are no new vars on left side of :=
	//
	// no new variables on left side of :=
	// f, g := 9, 10

	// Since f is an existing variable, its type cannot be changed.
	//
	// constant 8.2 truncated to integer
	// f, h := 8.2, 9
	//
	// cannot use "bar" (type string) as type int in assignment
	// f, h := "bar", 9

	// h declared and not used
	// var h int = 9;

	// i declared and not used
	// var i int
	// i = 10

	var j int
	j = 10
	j = j + 2
}

func getValue() int {
	return 4
}
