package main

import "fmt"

func main() {
	// Errors from 'go vet':
	//
	// fmt.Println call has possible Printf formatting directive %s
	// fmt.Printf format %s has arg 10 of wrong type int
	fmt.Println("foo %s")
	fmt.Printf("foo %s\n", 10)

	// Fixed code.
	fmt.Printf("foo %%s")
	fmt.Printf("foo %d\n", 10)
}
