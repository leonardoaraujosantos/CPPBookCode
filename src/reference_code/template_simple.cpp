/*
Compile:
g++ template_simple.cpp -o template_simple
*/
#include <iostream>

// Avoid having to type std::
using namespace std;

// Bad because we need to have different versions for each type
int max (int x, int y) {
  // Ternary operator that return x if x>y otherwise return y
  return (x>y)? x: y;
}
float max (float x, float y) {
  // Ternary operator that return x if x>y otherwise return y
  //cout << "Going float" << endl;
  return (x>y)? x: y;
}

// Better because work for different types of data
template <class someType>
someType maxGen(someType x, someType y) {
  return (x>y)? x: y;
}


int main() {
  cout << "Simple use of templates" << endl;
  cout << "Version for integer, max(2,4)=" << max(2,4) << endl;
  cout << "Version for double, max(2.0,4.1)=" << max(2.0,4.1) << endl;
  cout << "Generic version, maxGen<float>(2.0,4.1)=" << maxGen<float>((float)2.0,(float)4.1) << endl;

  return 0;
}
