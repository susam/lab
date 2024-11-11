package main

import (
	"fmt"
)

func main() {
	a := [5]int{10, 20, 30, 40, 50}
	b := a[1:4]
	b[1] = 100
	fmt.Println("a:", a)
	fmt.Println("b:", b)

	s := "hello"
	fmt.Println("s[1:4]:", s[1:4])
	fmt.Println("s[0:4]:", s[0:4])
	fmt.Println("s[:4]:", s[:4])
	fmt.Println("s[3:5]:", s[3:5])
	fmt.Println("s[3:]:", s[3:])
	fmt.Println("s[:]:", s[:])

	// invalid slice index -1 (index must be non-negative)
	// fmt.Println("s[3:-1]:", s[3:-1])

	// runtime error: slice bounds out of range
	// fmt.Println("s[3:6]:", s[3:6])

	c := []int{10, 20, 30, 40, 50}
	c = removeAtIndex(c, 2)
	fmt.Println("c:", c)

	d := []int{10, 20, 30, 40, 50}
	e := make([]int, 3)

	copy(e, d[1:4]) // e: [20 30 40]
	fmt.Println("e:", e)

	copy(e[1:], d[3:]) // e: [20 40 50]
	fmt.Println("e:", e)

	copy(e, d) // e: [10, 20, 30]
	fmt.Println("e:", e)

	copy(e, d[3:]) // e: [40, 50, 30]
	fmt.Println("e:", e)
}

func removeAtIndex(src []int, index int) []int {
	lastIndex := len(src) - 1
	src[index], src[lastIndex] = src[lastIndex], src[index]
	return src[:lastIndex]
}
