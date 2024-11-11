package main

import (
	"fmt"
)

func main() {
	var a []int = []int{10, 20, 30}
	fmt.Println("a:", a)
	fmt.Println("len(a):", len(a))
	fmt.Println("cap(a):", cap(a))

	for i, n := range a {
		fmt.Println(i, "=>", n)
	}
	fmt.Println()

	var b []int = make([]int, 5)
	fmt.Println("b:", b)
	fmt.Println("len(b):", len(b))
	fmt.Println("cap(b):", cap(b))
	fmt.Println()

	var c []int = make([]int, 2, 5)
	c[1] = 10
	// panic: runtime error: index out of range
	// c[2] = 10

	fmt.Println("c:", c)
	fmt.Println("len(c):", len(c))
	fmt.Println("cap(c):", cap(c))
	fmt.Println()

	c = append(c, 20)
	fmt.Println("After append: c:", c)
	fmt.Println("len(c):", len(c))
	fmt.Println("cap(c):", cap(c))
	fmt.Println()

	// panic: runtime error: index out of range
	// c[3] = 30

	// panic: runtime error: slice bounds out of range
	// c = c[0:6]
	c = c[0:5]
	fmt.Println("After reslice: c[0:5]:", c)

	c = c[0:4]
	c[3] = 30
	fmt.Println("After reslice: c[0:4]:", c)
	fmt.Println("len(c):", len(c))
	fmt.Println("cap(c):", cap(c))
	fmt.Println()

	c = c[1:3]
	fmt.Println("After reslice: c[1:3]:", c)

	var d []int
	fmt.Println("d:", d)
	fmt.Println("len(d):", len(d))
	fmt.Println("cap(d):", cap(d))

	d = append(d, 10)
	d = append(d, 20)
	d = append(d, 30)

	fmt.Println("d:", d)
	fmt.Println("len(d):", len(d))
	fmt.Println("cap(d):", cap(d))
}
