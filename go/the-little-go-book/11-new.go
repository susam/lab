package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	p1 := new(Person)
	fmt.Println("p1:", p1)

	p2 := &Person{}
	fmt.Println("p2:", p2)

	var p3 *Person = new(Person)
	fmt.Println("p3:", p3)

	var a *int = new(int)
	fmt.Println("a:", a)
	fmt.Println("*a:", *a)
}
