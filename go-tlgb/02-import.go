package main

import "fmt"

/*
Duplicate import leads to error.

# command-line-arguments
./02-import.go:4: fmt redeclared as imported package name
	previous declaration at ./02-import.go:3
*/
// import "fmt"

/*
Another way of doing import. gofmt is fine with it.

import (
	"fmt"
)
*/

func main() {
	fmt.Println("hello, world")
}
