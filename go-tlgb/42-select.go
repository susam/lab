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
	for {
		data = <-c
		fmt.Println("recv:", data)
		fmt.Println("sleeping ...")
		time.Sleep(time.Second * 2)
		fmt.Println("awake!")
	}
	fmt.Println("done")
}

func master(c chan int) {
	for i := 0; i < 10; i++ {
		fmt.Println("sending:", i, "...")
		select {
		case c <- i:
			fmt.Println("sent:", i)
		// Alternate messages are dropped.

		// If default case is commented out, then no messages
		// are dropped. Instead master blocks until worker
		// receives a message.
		default:
			fmt.Println("drop:", i)
		}
		time.Sleep(time.Second * 1)
	}
}
