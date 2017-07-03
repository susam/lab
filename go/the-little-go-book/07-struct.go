package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	var p0 Person = Person{
		Name: "John",
		Age:  30,
	}

	fmt.Println("p0:", p0)
	fmt.Println("p0.Name:", p0.Name)
	fmt.Println("p0.Age:", p0.Age)
	fmt.Println()

	p1 := Person{
		Age:  30,
		Name: "John",
	}

	fmt.Println("p1:", p1)
	fmt.Println("p1.Name:", p1.Name)
	fmt.Println("p1.Age:", p1.Age)
	fmt.Println()

	// syntax error: need trailing comma before newline in composite literal
	// syntax error: unexpected }
	/*
		p2 := Person{
			Name: "John",
			Age:  30
		}
	*/

	p3 := Person{}
	fmt.Println("p3:", p3)

	p3.Name = "Sally"
	p3.Age = 20
	fmt.Println("p3:", p3)

	p4 := Person{Name: "Jack"}
	fmt.Println("p4:", p4)

	p5 := Person{
		Name: "Jill",
	}
	fmt.Println("p5:", p5)

	p6 := Person{Age: 20}
	fmt.Println("p6:", p6)

	p7 := Person{Age: 20, Name: "Harry"}
	fmt.Println("p7:", p7)

	// cannot use 20 (type int) as type string in field value
	// cannot use "Harry" (type string) as type int in field value
	// p8 := Person{20, "Harry"}

	p9 := Person{"Harry", 20}
	fmt.Println("p9:", p9)

	// mixture of field:value and value initializers
	// p10 := Person{"Maverick", Age: 25}
}
