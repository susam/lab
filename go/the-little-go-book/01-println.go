package main

func main() {
	println("hello, world")
}

// If we rename package main to say main2, the following error would occur.
//
//     $ go run 01-println.go
//     go run: cannot run non-main package
//
// The following runs fine but no executable is generated.
//
//     $ go build 01-println.go
//     $ go build
//     $

// If we rename the func main to say main2, the following errors occur.
//
//     $ go run 01-println.go
//     # command-line-arguments
//     runtime.main: call to external function main.main
//     runtime.main: undefined: main.main
//
//     $ go build 01-println.go
//     # command-line-arguments
//     runtime.main: call to external function main.main
//     runtime.main: undefined: main.main
//
//     $ go build
//     # _/home/susam/git/alpha/lab/go/src/little
//     runtime.main: call to external function main.main
//     runtime.main: undefined: main.main

/*
Note that println may not be supported in future. fmt.Println should be
used in normal programs.

Here is a quote from <https://golang.org/ref/spec#Bootstrapping>.

Current implementations provide several built-in functions useful during
bootstrapping. These functions are documented for completeness but are
not guaranteed to stay in the language. They do not return a result.

Function   Behavior

print      prints all arguments; formatting of arguments is implementation-specific
println    like print but prints spaces between arguments and a newline at the end
*/
