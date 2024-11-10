package main

import (
	"crypto/sha256"
	"fmt"
	"math"
	"strings"
	"time"
)

func check(candidate []byte) {
	var msg string = "The SHA-256 hash of this text begins with " + string(candidate) + "."
	var digest [32]byte = sha256.Sum256([]byte(msg))
	var result string = fmt.Sprintf("%x", digest)
	if strings.HasPrefix(result, string(candidate)) {
		var result string = fmt.Sprintf("%x", digest)
		fmt.Println(msg)
		fmt.Println(result)
	}
}

func solve(length uint8) { // Let length <= 16.
	var chars string = "0123456789abcdef"
	var base uint8 = uint8(len(chars)) // Let base <= 16.
	var arrangement []uint8 = make([]uint8, length)
	var candidate []uint8 = make([]uint8, length)
	var maxCount uint64 = uint64(math.Pow(float64(base), float64(length))) // Then maxCount <= 16^16 = 2^64.
	var count uint64 = 0
	var chunkSize uint64 = 10_000_000
	var startTime time.Time = time.Now()
	fmt.Printf("solving for length %d with %d arrangements\n", length, maxCount)
	for {
		// Generate candidate message.
		for i := uint8(0); i < length; i++ {
			candidate[i] = chars[arrangement[i]]
		}

		// Check if the candidate message is a solution.
		check(candidate)

		// Compute the next arrangement used to generate the next candidate.
		var i uint8
		for i = 0; i == 0 || arrangement[i-1] == 0 && i < length; i++ {
			arrangement[i] = (arrangement[i] + 1) % base
		}

		// Log progress after every chunkSize iterations.
		count++
		if count%chunkSize == 0 || count == maxCount {
			var elapsed uint64 = uint64(time.Since(startTime).Milliseconds() / 1000)
			var remaining uint64 = (maxCount - count) * elapsed / count
			fmt.Printf("[%d s of %d s] checked chunk %d of %d\n",
				elapsed,
				remaining,
				(count+chunkSize-1)/chunkSize,
				(maxCount+chunkSize-1)/chunkSize,
			)
		}

		// Quit if there are no more arrangements to check.
		if i == length && arrangement[i-1] == 0 {
			break
		}
	}
	fmt.Println()
}

func main() {
	solve(7)
}
