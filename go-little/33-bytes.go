package main

import (
	"fmt"
)

func main() {
	a := "ABC"
	fmt.Println("a:", a)

	b := []byte(a)
	fmt.Println("b:", b)

	c := string(b)
	fmt.Println("c:", c)
	fmt.Println()

	d := "A♥"
	fmt.Println(d)
	fmt.Println([]byte(d))
	fmt.Println(len(d))
	fmt.Println(len([]byte(d)))
	fmt.Println()

	for i, rune := range d {
		fmt.Println(i, "=>", rune) // 65, 9829 (0x2665)
	}
	fmt.Println()

	for i, rune := range []byte(d) {
		fmt.Println(i, "=>", rune) // 65, 9829 (0x2665)
	}
	fmt.Println()

}
