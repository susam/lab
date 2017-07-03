package main

import (
	"23-pkg"
	"fmt"
)

func main() {
	/*
		cannot refer to unexported name bar.foo
		undefined: bar.foo
	*/
	// bar.foo()

	/*
		cannot refer to unexported name bar.bar
		undefined: bar.bar
	*/
	// bar.bar()

	/*
		undefined: bar.Bar
	*/
	// bar.Bar()

	bar.Foo()
	bar.CallFoo()
	bar.UsePerson()

	p := bar.Person{
		Name: "John",

		// unknown bar.Person field 'age' in struct literal
		// age:  10,
	}

	fmt.Println("p:", p)
}
