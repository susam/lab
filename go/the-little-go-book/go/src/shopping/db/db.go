package db

func GetPrice(id int) int {
	if id == 1 {
		return 10
	} else {
		return 20
	}
}

func getDealer(id int) string {
	if id == 1 {
		return "Dell"
	} else {
		return "Apple"
	}
}
