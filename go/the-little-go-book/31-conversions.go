package main

import (
	"fmt"
)

func main() {
	fmt.Println(add(10, 20))

	// panic: interface conversion: interface is float64, not int
	// fmt.Println(add(10.0, 20.0))
}

func add(a interface{}, b interface{}) interface{} {
	return a.(int) + b.(int)
}
