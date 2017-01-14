/*
Installing armadillo on ubuntu
g++ -std=c++11 armadillo_simple.cpp -o armadillo_simple -larmadillo
sudo apt-get install libarmadillo-dev libarmadillo4 r-cran-rcpparmadillo
*/
#include <iostream>
#include <armadillo>
#include <chrono>

using namespace std;
using namespace arma;

int main() {

  // Create a A[3,2]
  mat A = randu<mat>(3,2);
  //mat A = randu<mat>(1000,1000);
  // Create a A[2,3]
  mat B = randu<mat>(2,3);
  //mat B = randu<mat>(1000,1000);

  cout << "\n\nMatrix A" << endl;
  //cout << A;

  cout << "\n\nMatrix B" << endl;
  //cout << B;

  auto start = chrono::steady_clock::now();
  mat C = A*B;
  auto end = chrono::steady_clock::now();
  auto diff = end - start;

  cout << endl << "Execution time:"<< chrono::duration <double, milli> (diff).count() << " ms" << endl;

  // Do matrix multiplication
  cout << "\nResult:" << endl;
  //cout << A*B.t() << endl;
  cout << C << endl;

  return 0;
}
