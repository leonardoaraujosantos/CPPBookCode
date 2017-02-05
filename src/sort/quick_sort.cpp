/*
References:
http://rosettacode.org/wiki/Sorting_algorithms/Quicksort
https://www.youtube.com/watch?v=aQiWF4E8flQ&t=3s
https://www.youtube.com/watch?v=8hHWpuAPBHo
https://www.youtube.com/watch?v=39BV3_DONJc
https://www.youtube.com/watch?v=3OLTJlwyIqQ&t=188s
*/
#include <iostream>
#include <random>
#include <iterator>
#include <vector>

// We define the parameter as constant and reference because we don't want
// a copy and we also don't want to change he vector
void printVec(const std::vector<int> &vec) {
	// This is the for-each on C++11(14)
	std::cout << "[";
	for (auto i : vec) {
		std::cout << i << ", ";
	}
	std::cout << "]" << std::endl;
}

template<typename T, typename Container = std::vector<T>>
std::size_t partition(Container& array, std::size_t pivot, std::size_t left,
		std::size_t right) {
	T value = array[pivot];
	std::swap(array[pivot], array[right]);
	std::size_t store = left;
	for (size_t i = left; i < right; ++i) {
		if (array[i] <= value) {
			std::swap(array[i], array[store]);
			store++;
		}
	}
	std::swap(array[store], array[right]);
	return store;
}

template<typename T, typename Container = std::vector<T>>
void quicksort(Container& array, std::size_t left, std::size_t right) {
	if (left < right) {
		// Randomly choose the pivot.
		std::minstd_rand generator;
		std::uniform_int_distribution<> dist(left, right);
		// Find the new pivot from partitioning on a random pivot.
		std::size_t new_pivot = partition<T>(array, dist(generator), left,
				right);
		// Recurse as per usual.
		quicksort<T>(array, left, new_pivot - 1);
		quicksort<T>(array, new_pivot + 1, right);
	}
}

int main() {
	// Is not working for the worst-case investigate
	//std::vector<int> vec { 6, 6, 5, 4, 3, 2, 1 };
	std::vector<int> vec { 2, 4, 6, 7, 2, 1, 5 };

	std::cout << "Before sort" << std::endl;
	printVec(vec);

	quicksort<int>(vec, 0, vec.size() - 1);
	std::cout << "After sort (Merge sort)" << std::endl;
	printVec(vec);

	return 0;
}


