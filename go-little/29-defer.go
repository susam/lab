package main

import (
	"fmt"
)

func main() {
	fmt.Println("main(): start")
	defer defer1()
	fmt.Println("main(): middle")
	defer defer3()
	fmt.Println("main(): end")
}

func defer1() {
	fmt.Println("defer1(): start")
	defer2()
	fmt.Println("defer1(): end")
}

func defer2() {
	fmt.Println("defer2()")
}

func defer3() {
	fmt.Println("defer3()")
}
