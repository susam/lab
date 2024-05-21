package main

import (
	"fmt"
	"time"
)

func main() {
	t := time.Now()
	fmt.Println("t:", t)
	fmt.Println("t.UTC():", t.UTC())
	fmt.Println("t.Unix():", t.Unix())
	fmt.Println("t.UTC().Unix():", t.UTC().Unix())
	fmt.Println("t.UnixNano():", t.UnixNano())
	fmt.Println("t.UTC().UnixNano():", t.UTC().UnixNano())
}
