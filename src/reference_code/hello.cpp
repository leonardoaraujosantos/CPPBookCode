/*
To compile:
g++ hello.cpp -o hello
To enable c++11 features
g++ -std=c++11 hello.cpp -o hello
*/

#include <iostream>

int main() {
  std::cout << "Hello world" << std::endl;

  /*
    The result will be on the same type of the bigger type on the right side
    of the expression
  */
  double someVar = 10/4;
  //double someVar = 10/4.0;
  //double someVar = float(10)/4;

  double answer;
  std::cout << "Type answer for 4/5" << std::endl;
  std::cin >> answer;

  // Check if is the right answer
  if (answer == someVar) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Incorrect should be:" << someVar << std::endl;
  }

  return 0;
}
