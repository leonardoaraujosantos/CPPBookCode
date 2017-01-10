/*
To compile:
g++ -std=c++11 oop_simple.cpp -o oop_simple
*/
#include <iostream>
using namespace std;

class Shape {
// Members available to everyone
public:
  // Pure virtual function (classes that derive from Shape need to implement)
  virtual int getArea() = 0;

  void setWidth(int w) {
    width = w;
  }
  void setHeight(int h) {
    height = h;
  }
// Available only for child classes
protected:
  int width;
  int height;
};

// Child classes
class Rectangle: public Shape {
public:
  int getArea() {
    return width*height;
  }
};
class Triangle: public Shape {
public:
  int getArea() {
    return (width*height)/2;
  }
};

int main() {
  Rectangle rect;
  Triangle tri;

  rect.setWidth(50);
  rect.setHeight(70);
  cout << "Rectangle area:" << rect.getArea() << endl;

  tri.setWidth(50);
  tri.setHeight(70);
  cout << "Triangle area:" << tri.getArea() << endl;
}
