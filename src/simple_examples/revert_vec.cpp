#include <string>
#include <vector>
#include <iostream>

#include <stack>

using namespace std;

/*
 Maybe to much for reversing a vector O(2*n)
 */
std::vector<int> reverse_stack(std::vector<int> &v) {
	stack<int> myStack;
	// Iterate on vector
	for (auto i : v) {
		myStack.push(i);
	}

	// Pop all elements from stack (LIFO)
	int counter = 0;
	while (!myStack.empty()) {
		int item = myStack.top();
		myStack.pop();
		v[counter++] = item;
	}
	return v;
}

// Changing the argument to reference
// Seems faster O(n)
// v[ 4 3 2 1], will start from middle, ie: 2 v[2]=2
// v_rev[1 2 3 4]
std::vector<int> reverse(std::vector<int> &v) {
	// Detect odd/even size
	auto isOdd = v.size() % 2;
	// Add offset if needed
	auto offSet = (!isOdd) ? 1 : 2;
	auto start = v.size() / 2;

	// Create a copy to avoid changing own data
	// This will be O(n)
	vector<int> vCopy = v;

	// From half+offset vector downto beginning
	// This will be O(n/2)
	for (int i = start + offSet; i >= 0; --i) {
		std::swap(v[i], vCopy[v.size() - 1 - i]);
	}

	return v;
}

// Has error (Solved, improve...)
std::vector<int> reverse_orig(std::vector<int> v) {
	// From half+offset vector downto beginning
	// This will be O(n/2)
	for (unsigned int i = v.size() / 2; 0 <= i; --i) {
		std::swap(v[i], v[v.size() - 1 - i]);
	}
	return v;
}

int main() {
	vector<int> someVec {1,2,3,4};
	//vector<int> someVec { 1, 2, 3, 4, 5 };

	vector<int> someVec_rev = reverse(someVec);
	//vector<int> someVec_rev = reverse_stack(someVec);
	//vector<int> someVec_rev = reverse_orig(someVec);

	for (auto i:someVec_rev) {
		cout << i << endl;
	}
}
