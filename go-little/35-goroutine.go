package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("start")
	go process()
	time.Sleep(time.Second * 1)
	fmt.Println("done")

	fmt.Println("----------")

	go func() {
		for i := 0; i < 5; i++ {
			fmt.Println("f1:", i)
			time.Sleep(time.Second * 1)
		}
	}()

	go func() {
		for i := 0; i < 5; i++ {
			fmt.Println("f2:", i)
			time.Sleep(time.Second * 1)
		}
	}()

	time.Sleep(time.Second * 6)
}

func process() {
	fmt.Println("processing ...")
}
