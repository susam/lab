package main

import (
	"fmt"
	"os"
	// ./03-imports.go:6: imported and not used: "math"
	// "math"
)

/* Can also be written as two separate import statements. gofmt is fine
 * with it. */
// import "fmt"
// import "os"

/*
Duplicate import leads to error.

# command-line-arguments
./02-import.go:4: fmt redeclared as imported package name
	previous declaration at ./02-import.go:3
*/
// import "fmt"

/*
Another way of doing import.

import (
    "fmt"
)
*/

func main() {
	fmt.Println("len(os.Args):", len(os.Args))
	fmt.Println("os.Args:", os.Args)

	if len(os.Args) != 2 {
		fmt.Println("Error: Specify one argument.")
		os.Exit(1)
	}

	fmt.Println("Argument:", os.Args[1])
}
