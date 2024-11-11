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
	for data != 4 {
		data = <-c
		fmt.Println("recv:", data)
	}
	fmt.Println("done")
}

func master(c chan int) {
	for i := 0; i < 5; i++ {
		c <- i
		fmt.Println("sent:", i)
		time.Sleep(time.Second * 1)
	}
}
