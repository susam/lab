package main

import (
	"fmt"
	"io"
)

func main() {
	var i int
	var j int
	var s string
	ret, err := fmt.Scan(&i, &j, &s)
	fmt.Println("ret:", ret)
	fmt.Println("err:", err)

	if err == io.EOF {
		fmt.Println("EOF:", i, j, s)
	} else if err != nil {
		fmt.Println("Error:", i, j, s)
	} else {
		fmt.Println("scanned:", i, j, s)
	}
}
