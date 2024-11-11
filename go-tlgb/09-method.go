package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func (p *Person) setPerson1(name string, age int) {
	p.Name = name
	p.Age = age
	fmt.Println("p:", p)
}

func (p *Person) setPerson2(name string, age int) (string, int) {
	p.Name = name
	p.Age = age
	fmt.Println("p:", p)
	return name, age
}

func (p Person) setPerson3(name string, age int) {
	p.Name = name
	p.Age = age
	fmt.Println("p:", p)
}

func main() {
	p := Person{}

	p.setPerson1("Alice", 30)
	fmt.Println("p:", p)

	fmt.Println()

	name, age := p.setPerson2("Bob", 20)
	fmt.Println("returned:", name, age)
	fmt.Println("p:", p)
	fmt.Println()

	p.setPerson3("Charlie", 20)
	fmt.Println("p:", p)
	fmt.Println()
}
