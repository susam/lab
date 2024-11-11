/*
pkg21a already contains package foo. Defining another package foo in
pkg21b leads to the following errors in package main.

# command-line-arguments
./21-package-consistency.go:5: foo redeclared as imported package name
	previous declaration at ./21-package-consistency.go:4
./21-package-consistency.go:11: undefined: "pkg21b".Bar
*/
// package foo
package baz

func Foo() string {
	return "pkg21b/foo.go: baz.Foo()"
}
