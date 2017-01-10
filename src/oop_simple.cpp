/*
To compile:
g++ -std=c++11 oop_simple.cpp -o oop_simple
*/
#include <iostream>
using namespace std;

class Shape {
// Members available to everyone
public:
  // Default constructor (Explicit)
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

  // Virtual function that could (or not) be overrided on the base class
  virtual void displayInfo() {
    cout << "I'm a Shape width:" << width << " height:" << height << endl;
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
  void displayInfo() override {
    cout << "I'm a Rectangle width:" << width << " height:" << height << endl;
  }
};
class Triangle: public Shape {
public:
  // Call the base constructor
  Triangle(int w, int h): Shape(w,h) {};
  int getArea() {
    return (width*height)/2;
  }
  // If you comment here it will fall-back to the original base version
  void displayInfo() override {
    cout << "I'm a Triangle width:" << width << " height:" << height << endl;
  }
};

int main() {
  // Using default constructor (implicit)
  Rectangle rect;
  // New way to initialize on C++11
  Triangle tri = {50,70};

  // Set rect width/height
  rect.setWidth(50);
  rect.setHeight(70);

  // Display some information (should override behavior o child classes)
  rect.displayInfo();
  tri.displayInfo();

  // Get areaas
  cout << "Rectangle area:" << rect.getArea() << endl;
  cout << "Triangle area:" << tri.getArea() << endl;

  return 0;
}
