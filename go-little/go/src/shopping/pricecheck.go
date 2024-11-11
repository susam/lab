package shopping

import (
	"shopping/db"
)

func PriceCheck(id int) int {
	return db.GetPrice(id)
}
