package main

import (
	"fmt"
)

// The var statement declares a list of variables; as in function
// argument lists, the type is last.
var a, b int

// expected ';', found ','
// var x int, y string

// A var statement can be at package or function level.
var c string

// A var declaration can include initializers, one per variable.
var d, e float64 = 1.1, 2.2

// If an initializer is present, the type can be omitted; the variable
// will take the type of the initializer.
var f, g = 3.3, "foo"

// Outside a function, every statement begins with a keyword (var,
// func, and so on) and so the := construct is not available.
//
// expected declaration, found x
// x := 10

// missing init expr for z
// var x, y, z int = 10, 20

// missing init expr for z
// var x, y, z = 10, "foo"

func main() {
	packageVarsDemo()
	functionVarsDemo()
	shadowVarsDemo()
}

func packageVarsDemo() {
	fmt.Println("Package Variables Demo")
	fmt.Println("----------------------")
	fmt.Println()

	// a: 0, b: 0, c: ""
	fmt.Printf("a: %#v, b: %#v, c: %#v\n", a, b, c)

	// d: 1.1, e: 2.2, f: 3.3, g: "foo"
	fmt.Printf("d: %#v, e: %#v, f: %#v, g: %#v\n", d, e, f, g)

	fmt.Println()
	fmt.Println()
}

func functionVarsDemo() {
	fmt.Println("Function Variables Demo")
	fmt.Println("-----------------------")
	fmt.Println()

	// The var statement declares a list of variables; as in function
	// argument lists, the type is last.
	var p, q int

	// expected ';', found ','
	// var x int, y string

	// A var statement can be at package or function level.
	var r string

	// A var declaration can include initializers, one per variable.
	var s, t float64 = 1.1, 2.2

	// If an initializer is present, the type can be omitted; the
	// variable will take the type of the initializer.
	var u, v = 3.3, "foo"

	// Inside a function, the := short assignment statement can be
	// used in place of a var declaration with implicit type.
	m, n := 3.3, "foo"

	// Omission of type in var declaration seems to be useful only for
	// package-level variables.  Within a function, we can always use
	// the short assignment statement, so var declaration with type
	// omitted seems unnecessary within a function.

	// p: 0, q: 0, r: ""
	fmt.Printf("p: %#v, q: %#v, r: %#v\n", p, q, r)

	// s: 1.1, t: 2.2, u: 3.3, v: "foo"
	fmt.Printf("s: %#v, t: %#v, u: %#v, v: %#v\n", s, t, u, v)

	// m: 3.3, n: "foo"
	fmt.Printf("m: %#v, n: %#v\n", m, n)

	// missing init expr for z
	// var x, y, z int = 10, 20

	// missing init expr for z
	// var x, y, z = 10, 20

	// assignment mismatch: 3 variables but 2 values
	// x, y, z := 10, 20

	x, y, z := 10, 20, 30
	fmt.Printf("x: %#v, y: %#v, z: %#v\n", x, y, z)

	l, x, y, z := 10, 20, 30, 40
	fmt.Printf("l: %#v, x: %#v, y: %#v, z: %#v", l, x, y, z)

	// no new variables on left side of :=
	// l, x, y := 10, 20, 30

	fmt.Println()
	fmt.Println()
}

func shadowVarsDemo() {
	fmt.Println("Shadow Variables Demo")
	fmt.Println("---------------------")
	fmt.Println()

	// Shadow the package variables.
	var a string
	b := "hello"

	// local: a: "", b: "hello"
	fmt.Printf("local: a: %#v, b: %#v\n", a, b)

	// package: a: 0, b: 0
	printPackageVars()

	fmt.Println()
	fmt.Println()
}

func printPackageVars() {
	fmt.Printf("package: a: %#v, b: %#v\n", a, b)
}
