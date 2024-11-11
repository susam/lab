package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	a := Person{"John", 30}
	f(a)
	fmt.Println("a.Age:", a.Age) // Remains as 30

	b := &Person{"John", 30}
	g(b)
	fmt.Println("b.Age:", b.Age) // Modified to 32

	var c *Person = &Person{"Jack", 40}
	g(c)

	// Pointer is passed by value
	var d *Person
	h(d)
	fmt.Println("d:", d) // d remains as nil

	k(&d)
	fmt.Println("d:", d) // d points to Harry / 50
	fmt.Println("*d:", *d)

}

func f(p Person) {
	fmt.Println(p.Name, "/", p.Age)
	p.Age += 2
}

func g(p *Person) {
	fmt.Println(p.Name, "/", p.Age)
	p.Age += 2
}

func h(p *Person) {
	p = &Person{"Harry", 50}
}

func k(p **Person) {
	*p = &Person{"Harry", 50}
}
