/*
References:
https://en.wikipedia.org/wiki/C%2B%2B11#Range-based_for_loop
http://kbokonseriousstuff.blogspot.co.uk/2011/09/using-reverse-iterators-with-c11-range.html

To compile:
g++ -std=c++11 new_for_iteration.cpp -o new_for_iteration
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
	// Create an array with 5 elements
	int my_array[5] = {10, 20, 30, 40, 50};

	// Iterate on each element of the array
	cout << "\n\nFor-each array" << endl;
	auto posArray = 0;
	for (auto& x :my_array) {
		cout << "my_array[" << posArray << "]=" << x << endl;
		posArray++;
	}

	// Iterate on each element of the vector
	cout << "\n\nFor-each vector" << endl;
	posArray = 0;
	vector<int> my_vector{1, 2, 3, 4};
	for (auto& x :my_vector) {
		cout << "my_vector[" << posArray << "]=" << x << endl;
		posArray++;
	}
}