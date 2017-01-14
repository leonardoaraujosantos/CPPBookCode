/*
To compile:
g++ -std=c++11 old_pointers_references.cpp -o old_pointers_references
Check leaks with valgrind
valgrind  --leak-check=full ./old_pointers_references
Check the "definitely lost" errors
Reference for valgrind:
https://www.youtube.com/watch?v=fvTsFjDuag8
*/
#include <iostream>
#include <string>
using namespace std;

class Human {
public:
	~Human() {
		cout << "Human destructor??" << endl;
	}
	string m_name;
	int m_age;
	string m_phone;
};

int main() {
	// Allocate a integer on the heap
	int *ptr_a = new int;

	*ptr_a = 5;
	cout << "inside memory pointed by ptr_a: " << *ptr_a << " address on ptr_a: " << ptr_a << endl; 
	// Give back memory to the OS
	delete ptr_a;

	// Now you cannot get a (the value is undefined)
	//cout << " inside a: " << *a << endl;

	// Allocate an integer of the stack
	int var_b = 10;
	// a point to var_b
	ptr_a = &var_b;
	*ptr_a = 9;
	cout << "var_b=" << var_b << endl;

	// References (you point only once)
	int &ref_var_b = var_b;

	// Some change on the reference will chage the refered variable
	ref_var_b = 99;
	cout << "var_b=" << var_b << endl;

	// Allocating arrays
	int *array_int = new int[4]{11,21,31,41};
		
	// Pointer arithimetic
	*(array_int+2) = 99;
	array_int[3] = 3;

	for (auto i = 0; i < 4; i++) {
		cout << array_int[i] << endl;
	}

	// Use this otherwise you will have a leak
	delete[] array_int;
	// This will leak because it will free just one integer
	//delete array_int; 

	Human *pHuman = new Human;
	pHuman->m_age = 10;
	pHuman->m_phone = string("22339301");
	pHuman->m_name = string("Leonardo");
	(*pHuman).m_age = 35;
	cout << "Human name is: " << pHuman->m_name << endl;
	delete pHuman;

	return 0;
}
