#include <iostream>
#include <vector>
#include <algorithm>

// We define the parameter as constant and reference because we don't want
// a copy and we also don't want to change he vector
void printVec(const std::vector<int> &vec) {
	// This is the for-each on C++11(14)
	std::cout << "[" ;
	for (auto i : vec) {
		std::cout << i << ", ";
	}
	std::cout << "]" << std::endl;
}

// The buble sort algorithm has wort-case complexity O(n^2)
// We have 2 idented loops so O(n*n)
template<typename Iter>
void bubleSort(Iter first, Iter last) {
	auto neededSwap = true;
	// Keep record with the beginning of the vector
	auto beg = first;
	// Keep ordering until we run the whole container without need to reorder
	while (neededSwap) {
		// Reposition iterators
		first = beg;
		neededSwap = false;
		// Iterate on container
		for (; first != last; ++first) {
			// Check if we have no other pair
			if ((first + 1) != last) {
				// Order the pair if needed
				if (*first > *(first + 1)) {
					// Swap
					/*auto value2 = *(first + 1);
					*(first + 1) = *first;
					*first = value2;*/
					std::swap(*first, *(first+1));
					neededSwap = true;
				}
			}
		}
	}
}

int main() {
	std::vector<int> vec { 6, 5, 4, 3, 2, 1 };
	std::cout << "Before sort" << std::endl;
	printVec(vec);

	// Use std::sort to sort vector
	//std::sort(vec.begin(), vec.end());
	bubleSort(vec.begin(), vec.end());

	std::cout << "After sort" << std::endl;
	printVec(vec);

	return 0;
}

