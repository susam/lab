package main

import (
	"fmt"
)

type Person interface {
	// syntax error: unexpected name, expecting (
	// Name string
	Hello(message string)
	Bye(message string)
}

type Chef struct {
	Name string
}

func (c Chef) Hello(message string) {
	fmt.Println("Hello, my name is", c.Name, "and I am a Chef.", message)
}

func (c Chef) Bye(message string) {
	fmt.Println(message, "Bye!")
}

func main() {
	var c Chef = Chef{
		Name: "Charlie",
	}
	invokeHello(c)
}

func invokeHello(p Person) {
	p.Hello("How are you?")
}
