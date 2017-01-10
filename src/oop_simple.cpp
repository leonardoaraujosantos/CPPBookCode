/*
To compile:
g++ -std=c++11 oop_simple.cpp -o oop_simple
*/
#include <iostream>
using namespace std;

class Shape {
// Members available to everyone
public:
  // Default constructor
  Shape() = default;
  // Another constructor that already initialize width and height
  Shape(int w, int h) : width(w),height(h){};
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
  // C++11 allows initialize members on class declaration
  int width = 0;
  int height = 0;
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
  // Call the base constructor
  Triangle(int w, int h): Shape(w,h) {};
  int getArea() {
    return (width*height)/2;
  }
};

int main() {
  Rectangle rect;

  // New way to initialize on C++11
  Triangle tri = {50,70};

  rect.setWidth(50);
  rect.setHeight(70);
  cout << "Rectangle area:" << rect.getArea() << endl;
  cout << "Triangle area:" << tri.getArea() << endl;
}
