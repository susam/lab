package main

import (
	"errors"
	"fmt"
	"strconv"
)

func main() {
	n, err := strconv.Atoi("123")
	fmt.Println("n:", n, "; err:", err)
	fmt.Printf("n: %d ; err: %s\n", n, err)
	fmt.Printf("n: %d ; err: %v\n\n", n, err)

	n, err = strconv.Atoi("123a")
	fmt.Println("n:", n, "; err:", err)
	fmt.Printf("n: %d ; err: %s\n", n, err)
	fmt.Printf("n: %d ; err: %v\n\n", n, err)

	n, err = incrPositiveInt(1)
	fmt.Println("n:", n, "; err:", err)
	fmt.Printf("n: %d ; err: %s\n", n, err)
	fmt.Printf("n: %d ; err: %v\n\n", n, err)

	n, err = incrPositiveInt(0)
	fmt.Println("n:", n, "; err:", err)
	fmt.Printf("n: %d ; err: %s\n", n, err)
	fmt.Printf("n: %d ; err: %v\n\n", n, err)

	n, err = incrPositiveInt(-1)
	fmt.Println("n:", n, "; err:", err)
	fmt.Printf("n: %d ; err: %s\n", n, err)
	fmt.Printf("n: %d ; err: %v\n\n", n, err)
}

func incrPositiveInt(n int) (int, error) {
	if n < 0 {
		return 0, errors.New("New Error: Negative integer")
	} else if n == 0 {
		return 0, DemoError{"Zero integer"}
	} else {
		return n + 1, nil
	}
}

type DemoError struct {
	Message string
}

func (e DemoError) Error() string {
	return "DemoError: " + e.Message
}
