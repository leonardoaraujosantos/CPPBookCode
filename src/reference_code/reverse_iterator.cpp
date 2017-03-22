/*
References:
https://en.wikipedia.org/wiki/C%2B%2B11#Range-based_for_loop
http://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
http://kbokonseriousstuff.blogspot.co.uk/2011/09/using-reverse-iterators-with-c11-range.html
https://www.youtube.com/watch?v=V89gtNl4pZM&index=2&list=PL5jc9xFGsL8E_BJAbOw_DH6nWDxKtzBPA
https://en.wikipedia.org/wiki/Decltype
http://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html

To compile:
g++ -std=c++11 reverse_iterator.cpp -o reverse_iterator
(use auto instead of decltype)
g++ -std=c++1y reverse_iterator.cpp -o reverse_iterator
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

/*
	Template class that gives const iterators
	rbegin instead of begin and rend instead of end
	If you comment this your for_range will still work but will not support
	const reverse itearators
*/
template<class T>
class const_reverse_wrapper {
private:
	const T& container;
public:
  const_reverse_wrapper(const T& cont) : container(cont){ }
	/*
		decltype will infer the datatype of the expression, on c++14 this can be
		infered with auto
	*/
	//decltype(container.rbegin()) begin() const { return container.rbegin(); }
	auto begin() const { return container.rbegin(); }
  //decltype(container.rend()) end() const { return container.rend(); }
	auto end() const { return container.rend(); }
};

template<class T>
const_reverse_wrapper<T> reverse(const T& cont) {
  return const_reverse_wrapper<T>(cont);
}

/*
	Template class that gives non-const iterators
	rbegin instead of begin and rend instead of end
	If you comment this your for_range will not be able to change data
*/
template<class T>
class reverse_wrapper {
private:
  T& container;
public:
  reverse_wrapper(T& cont) : container(cont){ }
	/*
		decltype will infer the datatype of the expression, on c++14 this can be
		infered with auto
	*/
  //decltype(container.rbegin()) begin() { return container.rbegin(); }
	auto begin() { return container.rbegin(); }
  //decltype(container.rend()) end() { return container.rend(); }
	auto end() { return container.rend(); }
};

template<class T>
reverse_wrapper<T> reverse(T& cont) {
  return reverse_wrapper<T>(cont);
}

int main() {
	// Create an array with 5 elements
	//int my_array[5] = {10, 20, 30, 40, 50};
	array<int,5> my_array = {10, 20, 30, 40, 50};

	// Reverse Iterate on each element of the array
	cout << "\n\nReverse iterator on array" << endl;
	auto posArray = my_array.size();
	for (auto it = my_array.rbegin(); it != my_array.rend(); ++it) {
		cout << "my_array[" << posArray << "]=" << *it << endl;
		posArray--;
	}

	// Iterate on each element of the vector
	cout << "\n\nReverse iterator on vector" << endl;
	vector<int> my_vector{1, 2, 3, 4};
	posArray = my_vector.size();
	for (auto it = my_vector.rbegin(); it != my_vector.rend(); ++it) {
		cout << "my_vector[" << posArray << "]=" << *it << endl;
		posArray++;
	}

	// Another option is to use the range based for loop, but with a proxy
	// template that will convert the iterators
	cout << "For_range approach (More verbose due to the proxy template)" << endl;
	posArray = my_vector.size();
	// auto &c will allow us to change the original container
	for (auto &c : reverse(my_vector)) {
		cout << "my_vector[" << posArray << "]=" << c << endl;
		c = 2;
		posArray++;
	}
	cout << "Vector my_vector: ";
	for_each(my_vector.begin(), my_vector.end(), [](int &n){ cout << n << " "; });
	cout << endl;
}
