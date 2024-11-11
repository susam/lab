// This example demonstrates that if the worker takes a long time to
// receive data from the channel, it blocks the sender.
package main

import (
	"fmt"
	"time"
)

func main() {
	c := make(chan int)
	go worker(c)
	master(c)
}

func worker(c chan int) {
	data := 0
	for data != 2 {
		data = <-c
		fmt.Println("recv:", data)
		time.Sleep(time.Second * 2)
	}
	fmt.Println("done")
}

func master(c chan int) {
	for i := 0; i < 3; i++ {
		// An unbuffered channel has length 0. A buffered
		// channel has length = number of items in the channel.
		fmt.Println("sending:", i, "; len(c):", len(c), "...")
		// master blocks for 2 seconds here until worker
		// receives i
		c <- i
		fmt.Println("sent:", i)
	}
}
