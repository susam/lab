package main

import (
	"fmt"
	"time"
)

func main() {
	c := 0

	for i := 0; i < 10; i++ {
		go func() {
			c++
			if c > 5 {
				time.Sleep(time.Millisecond * 10)
			}
			fmt.Println("c:", c)
		}()
	}

	time.Sleep(time.Second * 1)
}
