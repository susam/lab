package bar

import (
	"22-pkg/22-subpkgA"
	"fmt"
)

func Foo() {
	fmt.Println("22-pkg/foo.go: bar.Foo()")
	baz.Foo()
}
