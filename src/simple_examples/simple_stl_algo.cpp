#include <iostream>
#include <vector>
#include <list>
using namespace std;

/*
  Create simple function that look for a value inside
  a container (Vector, list, etc...)
  On this case the worst case will be O(n)
*/
template<typename iterT, typename T>
bool find_Value(iterT itBeg, iterT itEnd, const T val){
  // Look linear for a value
  for (; itBeg != itEnd; itBeg++) {
    // Consider the iterator as a pointer
    if (*itBeg == val)
      return true;
  }
  return false;
}

int main() {
  // Declare and define a vector using C++11 syntax
  vector<int> someValues = {1,2,3,4,5};
  
  // Iterate on all values of someValues (and print)
  cout << "Input container" << endl;
  for (const auto &vals : someValues) {
    cout << vals;
  }
  
  // Get value to find from keyboard
  auto val = 0;
  cout << endl << "Type a number that you wish to look for:";
  cin >> val;
  
  auto hasVal = find_Value(someValues.begin(), someValues.end(), val);
  cout << "Find value (" << val << ") returned:" << hasVal << endl;
  
  return 0;
}
