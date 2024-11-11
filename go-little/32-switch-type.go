package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

type Color struct {
	Name string
	r    int
	g    int
	b    int
}

func (p Person) SayHello() {
	fmt.Printf("Hello, I am %s.\n", p.Name)
}

func (c Color) PrintRGB() {
	fmt.Printf("rgb(%d, %d, %d)\n", c.r, c.g, c.b)
}

func main() {
	f(10)
	f(20.0)
	f(true)
	f("foo")
	f(Person{"Jack", 20})
	f(Color{"red", 255, 0, 0})
	fmt.Println()

	g(Person{"Jack", 20})
	g(Color{"red", 255, 0, 0})
}

func f(a interface{}) {
	switch a.(type) {
	case int:
		fmt.Println(a, "is int")

	case float64:
		fmt.Println(a, "is float64")

	case bool:
		fmt.Println(a, "is bool")

	case string:
		fmt.Println(a, "is string")

	default:
		fmt.Println(a, "is unknown")

	case Person:
		fmt.Println(a, "is Person")

	}
}

func g(a interface{}) {
	switch a.(type) {
	case Person:
		// a.SayHello undefined (type interface {} has no field
		// or method SayHello)
		// a.SayHello()
		a.(Person).SayHello()

	case Color:
		a.(Color).PrintRGB()
	}
}
