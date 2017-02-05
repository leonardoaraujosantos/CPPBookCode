#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>


int char2i(const char c){
	// Could be solved with a big switch or with the ASCII table
	int num = c - 48;
	return ((num > 9 || num < 0))? throw std::invalid_argument("Char is not a number") : num;
}

int atoi_my(const std::string &text){
	bool hasMinus = (text[0] == '-')? true : false;
	auto total = 0;
	for (auto it = text.begin(); it != text.end(); ++it){
		if (it==text.begin() && hasMinus)
			continue;
		total = (total*10) + char2i(*it);
	}
	if (hasMinus)
		total *= -1;
	return total;
}


int main() {
	try {
	std::string someTextNum = "-123";

	std::cout << "Type a n-digit number" << std::endl;
	std::cin >> someTextNum;
	std::cout << "Number was " << atoi_my(someTextNum) << std::endl;
	} catch(const std::exception& e) {
		std::cout << "Some error occured [" << e.what() << "]" << std::endl;
	}

	return 0;
}

