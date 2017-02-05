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


/*
 * Megesort, has better worst case complexity O(n*log(n)) but in practise can
 * be slower than quick sort due to cache miss.
 * Note that this solution is using recursion
 * */
template <typename T, typename Container=std::vector<T>>
void mergeSort(Container& array) {
  // Handle the base case a list with 1 element is already sorted
  // Also break the recursion
  if (array.size() <= 1) return;

  // The containers that get half of the array
  std::size_t middle = array.size() / 2;
  // Allocate each array to one half of the array.
  Container left(array.begin(), array.begin() + middle);
  Container right(array.begin() + middle, array.end());

  // Recursively divide those lists again
  // Using references, so we don't have a return.
  mergeSort<T>(left); // Acts as our left.
  mergeSort<T>(right);

  // Merge the results using std::merge, the beginning of the 2 containers
  // Notice that std::merge merge the containers by sorting them, so here
  // will be the magic....
  std::merge(left.begin(), left.end(), right.begin(), right.end(), array.begin());
}


int main() {
	std::vector<int> vec { 6, 5, 4, 3, 2, 1 };
	std::cout << "Before sort" << std::endl;
	printVec(vec);

	mergeSort<int>(vec);
	std::cout << "After sort (Merge sort)" << std::endl;
	printVec(vec);

	return 0;
}

