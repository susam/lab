package main

import "fmt"
import "time"
import "math"
import "math/rand"

func main() {
	fmt.Println("hello, world")
	fmt.Println("time:", time.Now())
	fmt.Println("pi:", math.Pi)
	fmt.Println("sqrt(2):", math.Sqrt(2))
	fmt.Println("random:", rand.Intn(10))
}
