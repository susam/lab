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
	// Alternate messages timeout
	for i := 0; i < 10; i++ {
		fmt.Println("sending:", i, "...")
		select {
		case c <- i:
			fmt.Println("sent:", i)
		case <-time.After(time.Second * 1):
			fmt.Println("timeout:", i)
		// Alternate messages drop. No timeouts occur.
		default:
			fmt.Println("drop:", i)
		}
		time.Sleep(time.Second * 1)
	}
}