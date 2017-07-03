package main

import (
	"fmt"
)

// interfaces
type Guy interface {
	Print()
}

type HelloGuy interface {
	Guy
	Hello()
}

type ByeGuy interface {
	Bye()
}

type SuperGuy interface {
	HelloGuy
	ByeGuy
}

// structs
type RealGuy struct {
	Name string
}

/*
If we do not implement Print() method, the following error occurs in the
invokeHelloGuy() call in main(). This occurs because HelloGuy is
composed of Guy which defines Print() method.

cannot use g (type RealGuy) as type HelloGuy in argument to invokeHelloGuy:
RealGuy does not implement HelloGuy (missing Print method)
*/
func (g RealGuy) Print() {
	fmt.Println(g.Name)
}

func (g RealGuy) Hello() {
	fmt.Println(g.Name, "says, \"Hello\"")
}

/*
If we do not implement Bye() method, the following error occurs in the
invokeSuperGuy() call in main(). This occurs because SuperGuy is
composed of ByeGuy which defines Bye() method.

cannot use g (type RealGuy) as type SuperGuy in argument to invokeSuperGuy:
RealGuy does not implement SuperGuy (missing Bye method)
*/
func (g RealGuy) Bye() {
	fmt.Println(g.Name, "says, \"Bye\"")
}

func main() {
	g := RealGuy{"Real John"}
	invokeHelloGuy(g)
	invokeSuperGuy(g)
}

func invokeHelloGuy(g HelloGuy) {
	g.Hello()
}

func invokeSuperGuy(g SuperGuy) {
	g.Hello()
}
