package main

import (
	"fmt"
)

type Person struct {
	Name string
	Age  int
}

func NewPerson(name string, age int) *Person {
	return &Person{
		Name: name,
		Age:  age,
	}
}

func NewPerson2(name string, age int) Person {
	return Person{
		Name: name,
		Age:  age,
	}
}

func main() {
	// cannot use NewPerson("John", 30) (type *Person) as type
	// Person in assignment
	// var p Person = NewPerson("John", 30)

	var q *Person = NewPerson("Jack", 40)
	fmt.Println("q:", q)
	fmt.Println("q:", *q)

	var r Person = NewPerson2("Jack", 40)
	fmt.Println("r:", r)
}
