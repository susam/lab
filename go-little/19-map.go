package main

import (
	"fmt"
)

func main() {
	var lookup map[string]int
	fmt.Println("lookup:", lookup)
	fmt.Println("len(lookup):", len(lookup))
	fmt.Println()

	// panic: runtime error: assignment to entry in nil map
	// lookup["foo"] = 10

	lookup = make(map[string]int)
	fmt.Println("lookup:", lookup)
	fmt.Println("len(lookup):", len(lookup))
	fmt.Println()

	lookup["foo"] = 1
	lookup["bar"] = 2
	lookup["baz"] = 3
	fmt.Println("lookup:", lookup)

	val, exists := lookup["foo"]
	fmt.Println("lookup[\"foo\"]: val:", val, "; exists:", exists)

	val, exists = lookup["qux"]
	fmt.Println("lookup[\"qux\"]: val:", val, "; exists:", exists)
	fmt.Println()

	delete(lookup, "foo")
	delete(lookup, "qux")
	fmt.Println("lookup:", lookup)
	fmt.Println("len(lookup):", len(lookup))

	// invalid argument lookup (type map[string]int) for ca
	// fmt.Println("cap(lookup):", cap(lookup))

	lookup = make(map[string]int, 100)
	fmt.Println("lookup:", lookup)           // map[]
	fmt.Println("len(lookup):", len(lookup)) // 0

	lookup = map[string]int{
		"foo": 10,
		"bar": 20,
		"baz": 30,
	}
	fmt.Println("lookup:", lookup)

	for key, val := range lookup {
		fmt.Println(key, "=>", val)
	}
}
