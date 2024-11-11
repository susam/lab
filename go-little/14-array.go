package main

import (
	"fmt"
)

func main() {
	var a [5]int

	a[0] = 1
	fmt.Println(a)

	var b [5]int = [5]int{2, 3, 4}
	fmt.Println(b)
	fmt.Println(len(b))
	fmt.Println()

	for i, n := range b {
		fmt.Println(i, "=>", n)
	}
	fmt.Println()

	// undefined: i
	// undefined: n
	// fmt.Println("i:", i)
	// fmt.Println("n:", n)

	var j, m int = 1, 2
	fmt.Println("j, m:", j, m)

	for j, m = range b {
		fmt.Println(j, "=>", m)
	}

	fmt.Println("j, m:", j, m) // 4, 0
	fmt.Println()

	var k, x int = 1, 2
	fmt.Println("k, x:", k, x)

	for k, x := range b {
		fmt.Println(k, "=>", x)
	}

	fmt.Println("k, x:", k, x) // 1, 2
	fmt.Println()

	// cannot use [4]int literal (type [4]int) as type [5]int in assignment
	// var b [5]int = [4]int{2, 3, 4}

	// cannot use [6]int literal (type [6]int) as type [5]int in assignment
	// var b [5]int = [6]int{2, 3, 4}

	// cannot use []int literal (type []int) as type [5]int in assignment
	// var b [5]int = []int{2, 3, 4, 5, 6}
}
