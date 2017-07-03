package baz

import (
	/*
		import cycle not allowed
		package 22-pkg
			imports 22-pkg/22-subpkgA
			imports 22-pkg
	*/
	// "22-pkg"
	"fmt"
)

func Foo() {
	fmt.Println("22-pkg/22-subpkgA/foo.go: baz.Foo()")
}
