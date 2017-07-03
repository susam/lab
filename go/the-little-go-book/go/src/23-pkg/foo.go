package bar

import (
	"fmt"
)

func foo() {
	fmt.Println("23-pkg/foo.go: bar.foo()")
}

func Foo() {
	fmt.Println("23-pkg/foo.go: bar.Foo()")
}

func CallFoo() {
	// undefined: bar
	// bar.foo()
	foo()
}

type Person struct {
	Name string
	age  int
}

func UsePerson() {
	p := Person{
		Name: "John",
		age:  10,
	}

	fmt.Println("p:", p, ":", p.Name, "/", p.age)
}
