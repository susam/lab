package main

import (
	"fmt"
)

// A var statement can be at package or function level. We see both in
// this example.
var a int
var b bool
var c string

// 07-variables.go:13:10: expected ';', found ','
// var d int, e string

var d, e int

func main() {
	// a: 0 (int), b: false (bool), c:  (string)
	fmt.Printf("a: %d (%T), b: %t (%T), c: %s (%T)\n", a, a, b, b, c, c)

	// a: 0 (int), b: false (bool), c:  (string)
	fmt.Printf("a: %v (%T), b: %v (%T), c: %v (%T)\n", a, a, b, b, c, c)

	// a: 0 (int), b: false (bool), c: "" (string)
	fmt.Printf("a: %#v (%T), b: %#v (%T), c: %#v (%T)\n", a, a, b, b, c, c)
}
