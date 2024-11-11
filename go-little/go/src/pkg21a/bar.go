/*
If pkg21a contains two Go files with different package declarations,
then an error occurs.

For example, if this file is declared to have 'package bar' instead of
'package foo', the following error is seen at the line in package main
where "pkg21a" is imported.
*/

// 21-package-consistency.go:6:2: found packages bar (bar.go) and foo
// (foo.go) in /home/susam/git/alpha/lab/go/little/go/src/pkg21a

// package bar
package foo

// go/src/pkg21a/foo.go:3: Foo redeclared in this block
// 	previous declaration at go/src/pkg21a/bar.go:16
/*
func Foo() string {
	return "bar.go: Foo()"
}
*/

func Bar() string {
	return "pkg21a/bar.go: foo.Bar()"
}
