/*
Installing armadillo on ubuntu
g++ -std=c++11 armadillo_simple.cpp -o armadillo_simple -larmadillo
sudo apt-get install libarmadillo-dev libarmadillo4 r-cran-rcpparmadillo
*/
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main() {

  // Create a A[3,2]
  mat A = randu<mat>(3,2);
  // Create a A[2,3]
  mat B = randu<mat>(2,3);

  cout << "\n\nMatrix A" << endl;
  cout << A;

  cout << "\n\nMatrix B" << endl;
  cout << B;

  // Do matrix multiplication
  cout << "\nResult:" << endl;
  //cout << A*B.t() << endl;
  cout << A*B << endl;

  return 0;
}
