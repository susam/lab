package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	fmt.Println("hello, world")
	fmt.Println("time:", time.Now())
	fmt.Println("pi:", math.Pi)
	fmt.Println("sqrt(2):", math.Sqrt(2))
	fmt.Println("random:", rand.Intn(10))
}
