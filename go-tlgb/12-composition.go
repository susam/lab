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

func (c *Coder) HelloCoder() {
	fmt.Println("Hello, I am a coder name", c.Name)
	fmt.Println("Hello, I am a coder name", c.Person.Name)
}

type Tester struct {
	Person
	Lang string
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
	c.HelloCoder()
	// c.Person.HelloCoder undefined (type *Person has no field or
	// method HelloCoder)
	// c.Person.HelloCoder()
	fmt.Println("c.Name:", c.Name)
	fmt.Println("c.Age:", c.Age)
	fmt.Println("c.Lang:", c.Lang)
	fmt.Println("c.Person.Name:", c.Person.Name)
	fmt.Println("c.Person.Age:", c.Person.Age)
	// c.Person.Lang undefined (type *Person has no field or method Lang)
	// fmt.Println("c.Person.Lang:", c.Person.Lang)
	fmt.Println()

	d := Coder{
		Person: &Person{
			Name: "Peter",
			Age:  60,
		},
		Lang: "Java",
	}
	d.Hello()
	d.Person.Hello()
	fmt.Println("d.Name:", d.Name)
	fmt.Println("d.Person.Name:", d.Person.Name)
	fmt.Println()

	t := &Tester{
		Person: Person{
			Name: "Moore",
			Age:  30,
		},
		Lang: "Python",
	}
	t.Hello()
	t.Person.Hello()
	fmt.Println("t.Name:", t.Name)
	fmt.Println("t.Person.Name:", t.Person.Name)
}
