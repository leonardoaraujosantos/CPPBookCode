/*
Tuples in C++11
Allows having a list of stuff with different data type, like a struct.

Where it can be used
1) It's useful to create functions that return multilple things
2) Can be used to create multi-index maps

References:
https://www.youtube.com/watch?v=33Y_5gOyi3Y&index=19&list=PL5jc9xFGsL8FWtnZBeTqZBbniyw0uHyaH

To compile:
g++ -std=c++11 tupple.cpp -o tupple
*/

#include <iostream>
#include <tuple>
#include <string>
#include <map>

using namespace std;

tuple <string, int> getNameAge() {
	return make_tuple("Leo",35);
}

int main() {
	// Pairs can only hold 2 elements
	pair<int, string> p = make_pair(23,"Hi");
	cout << p.first << ", " << p.second << endl;

	// Tuples are can have more elements
	tuple<int, string, double> t(10,"Leo",2.5);
	
	// Read tuples
	cout << get<0>(t) << endl;
	cout << get<1>(t) << endl;
	cout << get<2>(t) << endl;

	// You can also modify tuples
	get<2>(t) = 0.1;
	cout << get<2>(t) << endl;

	//tuple <string, int> nameAge = getNameAge();
	string name; int age;
	tie(name, age) = getNameAge();
	cout << "\nName and Age:" << name << " ," << age << endl;

	// Multi-index map
	map<tuple<int,char>, string> m;
	m[make_tuple(2,'a')] = "Some Item";
	return 0;
}