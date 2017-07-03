package main

import (
	"fmt"
	"time"
)

func main() {
	c := make(chan int)
	go worker(1, c)
	go worker(2, c)
	master(c)
}

func worker(id int, c chan int) {
	data := 0
	for data != 9 {
		data = <-c
		fmt.Printf("recv: %d (by worker %d)\n", data, id)
	}
	fmt.Printf("done (worker %d)\n", id)
}

func master(c chan int) {
	for i := 0; i < 10; i++ {
		c <- i
		fmt.Println("sent:", i)
		time.Sleep(time.Second * 1)
	}
}
