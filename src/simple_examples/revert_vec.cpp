#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
# include <omp.h>
#include <stack>

using namespace std;

/*
 Maybe to much for reversing a vector O(2*n)
 Actually with a big vector got much more slower
 */
template<class someType>
std::vector<someType> reverse_stack(std::vector<someType> &v) {
	stack<someType> myStack;
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
template<class someType>
std::vector<someType> reverse(std::vector<someType> &v) {
	// Detect odd/even size
	auto isOdd = v.size() % 2;
	// Add offset if needed
	auto offSet = (!isOdd) ? 1 : 2;
	auto start = v.size() / 2;

	// Create a copy to avoid changing own data
	// This will be O(n)
	vector<someType> vCopy = v;

	// From half+offset vector downto beginning
	// This will be O(n/2)
	for (int i = start + offSet; i >= 0; --i) {
		std::swap(v[i], vCopy[v.size() - 1 - i]);
	}

	return v;
}

template<class someType>
std::vector<someType> reverse_orig_fix(std::vector<someType> v) {
	// Detect odd/even size and calculate offset
	auto isOdd = v.size() % 2;
	auto offset = (!isOdd) ? 1 : 0;
	for (auto i = int(v.size() / 2) - offset; 0 <= i; --i) {
		//cout << "v[" << i << "]= v[" << destAddr << "]" << endl;
		std::swap(v[i], v[v.size() - 1 - i]);
	}
	return v;
}

template<class someType>
std::vector<someType> reverse_orig_fix_par(std::vector<someType> v) {
	// Detect odd/even size and calculate offset
	auto isOdd = v.size() % 2;
	auto offset = (!isOdd) ? 1 : 0;
	#pragma omp parallel for
	for (auto i = int(v.size() / 2) - offset; 0 <= i; --i) {
		//cout << "v[" << i << "]= v[" << destAddr << "]" << endl;
		std::swap(v[i], v[v.size() - 1 - i]);
	}
	return v;
}

// Has error (Solved, improve...)
std::vector<int> reverse_orig(std::vector<int> v) {
	// From half+offset vector downto beginning
	// This will be O(n/2)
	for (unsigned int i = v.size() / 2; i <= 0; --i) {
		std::swap(v[i], v[v.size() - 1 - i]);
	}
	return v;
}

int main() {
	vector<int> someVec {1,2,3,4};
	//vector<int> someVec { 1, 2, 3, 4, 5 };

	//vector<int> someVec_rev = reverse<int>(someVec);
	vector<int> someVec_rev = reverse_stack<int>(someVec);
	//vector<int> someVec_rev = reverse_orig(someVec);
	//vector<int> someVec_rev = reverse_orig_fix<int>(someVec);

	for (auto i : someVec_rev) {
		cout << i << endl;
	}

	// Create a very big vector
	vector<double> bigVec(100000000);
	std::generate(bigVec.begin(), bigVec.end(), std::rand);

	// Measure time
	auto start = chrono::steady_clock::now();
	// Insert rev code here....
	vector<double> bigVec_rev = reverse_orig_fix<double>(bigVec);
	//vector<double> bigVec_rev = reverse_stack<double>(bigVec);
	//vector<double> bigVec_rev = reverse<double>(bigVec);
	// Parallel version with openmp is 3x faster
	vector<double> bigVec_rev = reverse_orig_fix_par<double>(bigVec);
	auto end = chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time in ms: " << elapsed.count() << '\n';

}

