#include <iostream>
using namespace std;

class Rectangle {
protected:
  int width, height;

public:
  virtual void setWidth(int w) { width = w; }
  virtual void setHeight(int h) { height = h; }
  int getArea() const { return width * height; }
};

// Square "is-a" Rectangle geometrically, but violates LSP as a subclass
class Square : public Rectangle {
public:
  void setWidth(int w) override {
    width = w;
    height = w; // forces height to match width
  }
  void setHeight(int h) override {
    width = h; // forces width to match height
    height = h;
  }
};

// This function works correctly for ANY proper Rectangle
void testArea(Rectangle &r) {
  r.setWidth(5);
  r.setHeight(4);
  cout << "Expected area: 20, Got: " << r.getArea() << endl;
}

int main() {
  Rectangle rect;
  testArea(rect); // Expected area: 20, Got: 20  -- correct

  Square sq;
  testArea(sq); // Expected area: 20, Got: 16  -- WRONG!
}