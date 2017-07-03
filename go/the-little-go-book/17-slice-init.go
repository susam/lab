package main

import (
	"fmt"
)

func main() {
	// When we know the values.
	names := []string{"Alice", "Bob", "Charlie", "Dave"}

	// When we'll be writing into specific indexes of a slice
	flags := make([]bool, 5)

	// nil slice, populated with append()
	var cities []string

	// When we have a general idea of how many elements we'll need
	days := make([]string, 0, 7)

	fmt.Println("names:", names)

	flags[1] = false
	flags[2] = true
	fmt.Println("flags:", flags)

	cities = append(cities, "Bangalore")
	cities = append(cities, "Mangalore")
	fmt.Println("cities:", cities)

	days = append(days, "Sunday")
	days = append(days, "Monday")
	fmt.Println("days:", days)
}
