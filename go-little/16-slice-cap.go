package main

import (
	"fmt"
)

func main() {
	a := make([]int, 0, 5)
	fmt.Println("a:", a)
	fmt.Println("len(a):", len(a), "- cap(a):", cap(a))

	for i := 0; i < 25; i++ {
		a = append(a, i)
		fmt.Println(i, "=> len(a):", len(a), "- cap(a):", cap(a))
	}

	b := make([]int, 0)
	fmt.Println("b:", b)
	fmt.Println("len(b):", len(b), "- cap(b):", cap(b))

	for i := 0; i < 10; i++ {
		b = append(b, i)
		fmt.Println(i, "=> len(b):", len(b), "- cap(b):", cap(b))
	}

	var c []int
	fmt.Println("c:", c)
	fmt.Println("len(c):", len(c), "- cap(c):", cap(c))

	for i := 0; i < 3; i++ {
		c = append(c, i)
		fmt.Println(i, "=> len(c):", len(c), "- cap(c):", cap(c))
	}
}
