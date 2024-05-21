package main

import "fmt"

// A function can take zero or more arguments.  Notice that the type
// comes *after* the variable name.
func add1(x int, y int) int {
	return x + y
}

// When two or more consecutive named function parameters share a
// type, you can omit the type from all but the last.
func add2(x, y int) int {
	return x + y
}

func add3(x, y int, p, q int) int {
	return x + y + p + q
}

// A function can return any number of results.
func swap(x, y string) (string, string) {
	return y, x
}

func ints() (int, int, int) {
	return 10, 20, 30
}

func vals() (int, string) {
	return 10, "foo"
}

// Go's return values may be named.  If so, they are treated as
// variables defined at the top of the function.  These names should
// be used to document the meaning of the return values.
func ints2() (x, y, z int) {
	x = 10
	y = 20
	z = 30

	// A return statement without arguments returns the named return
	// values.  This is known as a "naked" return.
	return
}

func ints3() (x, y, z int) {
	y = 20
	return
}

func ints4() (x, y, z int) {
	y = 20
	return 100, 200, 300
}

func ints5() (x, y, z int) {
	y = 20

	// not enough return values
	// return 100, 200

	// If the code terminates here, we get the following compiler error:
	// missing return

	return 400, 500, 600
}

func main() {
	fmt.Println("add1:", add1(10, 20))
	fmt.Println("add2:", add2(10, 20))
	fmt.Println("add3:", add3(10, 20, 30, 40))

	// multiple-value swap("foo", "bar") (value of type (string, string)) in single-value context
	// fmt.Println("swap:", swap("foo", "bar"))

	fmt.Printf("swap: ")
	fmt.Println(swap("foo", "bar")) // bar foo

	fmt.Printf("ints: ")
	fmt.Println(ints()) // 10 20 30

	fmt.Printf("vals: ")
	fmt.Println(vals()) // 10 foo

	fmt.Printf("ints2: ")
	fmt.Println(ints2()) // 10 20 30

	fmt.Printf("ints3: ")
	fmt.Println(ints3()) // 0 20 0

	fmt.Printf("ints4: ")
	fmt.Println(ints4()) // 100 200 300

	fmt.Printf("ints5: ")
	fmt.Println(ints5()) // 400 500 600

}
