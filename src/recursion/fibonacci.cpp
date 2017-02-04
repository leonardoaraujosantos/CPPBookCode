#include <iostream>

/*
 * Example of recursion to calculate the fibonaci, it's really elegant
 * but could be
 * */
int fibo(const int n) {
	// We always need a finish to a recursion
	if (n == 1){
		return 1;
	} else {
		// Recursion here...
		int result = n * fibo(n-1);
		return result;
	}
}

int main() {
	std::cout << "10! (10*9!) is " << fibo(10) << std::endl;
	return 0;
}

