/*
To compile:
g++ -std=c++11 new_pointer_cpp11.cpp -o new_pointer_cpp11
Check leaks with valgrind
valgrind  --leak-check=full ./new_pointer_cpp11
Check the "definitely lost" errors
Reference for valgrind:
https://www.youtube.com/watch?v=fvTsFjDuag8

More references on C++11 Shared pointer
http://stackoverflow.com/questions/21589595/does-using-reset-on-a-stdshared-ptr-delete-all-instances
https://mbevin.wordpress.com/2012/11/18/smart-pointers/
http://stackoverflow.com/questions/6876751/differences-between-unique-ptr-and-shared-ptr
http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
*/
#include <iostream>
#include <memory>

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

/*
	The main idea is that now we don't need to take care 
	about doing the delete anymore.
*/
int main(){
	// Allocate a integer on the heap with smart pointers
	//shared_ptr<int> ptr_a = shared_ptr<int>(new int);
	shared_ptr<int> ptr_a (new int);
	*ptr_a = 5;
	cout << "inside memory pointed by ptr_a: " << *ptr_a << " address on ptr_a: " << ptr_a << endl; 

	/*
		This is a danger, don't point smart pointers to things on the
		stack, this will crash the program
	*/
	/*// Allocate an integer of the stack
	int var_b = 10;
	// ptr_a point to var_b (Reset and point to somewhere else)
	// Most cool this will not leak! (If var_b) would be on stack
	ptr_a.reset(&var_b);
	*ptr_a = 9;
	cout << "var_b=" << var_b << endl;	*/

	// Allocating arrays
	//shared_ptr<int> array_int = shared_ptr<int>(new int[4],std::default_delete<int[]>());
	unique_ptr<int[]> array_int = unique_ptr<int[]>(new int[4]{11,21,31,41});
		
	// Pointer arithimetic
	//*(array_int+2) = 99;
	array_int[2] = 99;
	array_int[3] = 3;

	for (auto i = 0; i < 4; i++) {
		cout << array_int[i] << endl;
	}

	// Using on objects
	shared_ptr<Human> pHuman = shared_ptr<Human>(new Human);
	pHuman->m_age = 10;
	pHuman->m_phone = string("22339301");
	pHuman->m_name = string("Leonardo");
	(*pHuman).m_age = 35;
	cout << "Human name is: " << pHuman->m_name << endl;

	return 0;
}
