/*
To compile:
g++ -std=c++11 operator_overload.cpp -o operator_overload
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

class DeepModel {
public:
  DeepModel(string p_name):m_name(p_name){};

  // Override the "<=" operator to add something on the layer vector
  // Reference: http://en.cppreference.com/w/cpp/language/operators
  void operator<=(string p_layer){
    m_layerVec.push_back(p_layer);
  }

  // Display some information
  void displayInfo(){
    cout << "Model name: " << m_name << endl;
    cout << "Layers: " << m_layerVec.size() << endl;

    // New way C++11 way to iterate on vector, (By value on this case)
    for (auto it_vector : m_layerVec) {
      cout << "\tL:" << it_vector << endl;
    }
  }
protected:
  vector<string> m_layerVec;
  string m_name;
};

int main() {
  DeepModel hypothesis("CNN_Model");
  hypothesis <= string("CONV");
  hypothesis <= string("RELU");
  hypothesis <= string("MAX_POOL");
  hypothesis <= string("CONV");
  hypothesis <= string("RELU");
  hypothesis <= string("MAX_POOL");
  hypothesis <= string("FC");
  hypothesis <= string("RELU");
  hypothesis <= string("FC");
  hypothesis <= string("SOFTMAX");

  hypothesis.displayInfo();
  return 0;
}
