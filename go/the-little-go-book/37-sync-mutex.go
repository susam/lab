package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	c := 0
	var lock sync.Mutex

	for i := 0; i < 10; i++ {
		go func() {
			lock.Lock()
			defer lock.Unlock()
			c++
			if c > 5 {
				time.Sleep(time.Millisecond * 10)
			}
			fmt.Println("c:", c)
		}()
	}

	time.Sleep(time.Second * 1)
}
