// This example demonstrates that a buffered channel with a capacity of
// 5 readily accepts 5 values but begins blocking with the 6th value.
package main

import (
	"fmt"
	"time"
)

func main() {
	c := make(chan int, 5)
	go worker(c)
	master(c)
}

func worker(c chan int) {
	data := 0
	for {
		data = <-c
		fmt.Println("recv:", data)
		time.Sleep(time.Second * 2)
	}
	fmt.Println("done")
}

func master(c chan int) {
	// Since chan is defined as buffered with capacity 5, the first
	// 5 values sent to the channel do not block. The 6th value sent
	// to the channel blocks.
	for i := 0; i < 10; i++ {
		fmt.Println("sending:", i, "; len(c):", len(c), "...")
		c <- i
		fmt.Println("sent:", i)
	}
}
