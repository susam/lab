package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func (p *Person) Hello() {
	fmt.Println("Hello, I am", p.Name)
}

type Coder struct {
	*Person
	Lang string
}

func (c *Coder) Hello() {
	fmt.Println("Hello, I am a coder named", c.Name)
}

func main() {
	c := &Coder{
		Person: &Person{
			Name: "Dennis",
			Age:  60,
		},
		Lang: "C",
	}
	c.Hello()
	c.Person.Hello()
}
