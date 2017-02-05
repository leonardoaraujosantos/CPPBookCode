#include <iostream>
#include <vector>
#include <iterator>

// For work the binary search need a sorted input
template<typename T, typename Container = std::vector<T>>
int binary_search(Container& array, T value) {
	// Handle the array being of size 0.
	if (array.size() == 0)
		return -1;

	// Handle the array being of size 1.
	if (array.size() == 1)
		return array[0] == value ? 0 : -1;


	int left = 0;
	int right = array.size();

	while (right >= left) {
		// Calculate the left most value.
		int middle = (left + right) / 2;

		// Get the value on the middle, if is smaller result must be on the left
		if (array[middle] < value) {
			left = middle + 1;
			// If it's bigger than the result must be to our right
		} else if (array[middle] > value) {
			right = middle - 1;
			// Else we have found it.
		} else {
			return middle;
		}
	}
	return -1;
}

int main() {
	// Ordered vector
	std::vector<int> order_vec { 1, 2, 3, 4, 5, 6, 7, 8 };

	std::cout << "Input ordered vector: [";
	// Other way to print this vector
	std::copy(order_vec.begin(), order_vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "]" << std::endl;

	// Look for value 7
	auto pos = binary_search<int>(order_vec, 7);

	// Test some values
	std::cout << "Value 7 is at position: " << pos << std::endl;
	return 0;
}

