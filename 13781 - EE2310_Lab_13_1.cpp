/*
Define a class Shape that contains two data members of int type: location_x and location_y. It also contains another data member color of string class (#include <string> for using the string class).
Shape contains 3 member functions get_x(), get_y(), get_color(), and a constructor Shape(int, int, string).
Define another two derived classes Rectangle and Triangle that inherit from Shape. Both of them have a constructor with 3 arguments (int, int, string). Note that in these constructors you need to use the C++ initializer list to call Shape's constructor, otherwise only the default constructor of Shape will be called.
Both Rectangle and Triangle have a member function output().
The main function is given as follows. Do not change it.

*/

#include <iostream>
#include <string>
using namespace std;

class Shape {
    private:
        int location_x;
        int location_y;
        string color;
    public:
        Shape(int x, int y, string c);
        int get_x();
        int get_y();
        string get_color();
};

Shape::Shape(int x, int y, string c) {
    location_x = x;
    location_y = y;
    color = c;
}

int Shape::get_x() {
    return location_x;
}

int Shape::get_y() {
    return location_y;
}

string Shape::get_color() {
    return color;
}

class Rectangle: public Shape {
    public:
        Rectangle(int x, int y, string c);
        void output();
};

Rectangle::Rectangle(int x, int y, string c): Shape(x, y, c) {}

//output : I'm a Rectangle: location_x = 10, location_y = 7, color = blue

void Rectangle::output() {
    cout << "I'm a Rectangle: location_x = " << get_x() << ", location_y = " << get_y() << ", color = " << get_color() << endl;
}

class Triangle: public Shape {
    public:
        Triangle(int x, int y, string c);
        void output();
};

Triangle::Triangle(int x, int y, string c): Shape(x, y, c) {}

//output : I'm a Triangle: location_x = 10, location_y = 5, color = black

void Triangle::output() {
    cout << "I'm a Triangle: location_x = " << get_x() << " , location_y = " << get_y() << ", color = " << get_color() << endl;
}

// Do NOT CHANGE main()! You may get penalty points.
int main() {
    Rectangle rec(10,7,"blue");
    Triangle  tri(10,5,"black");

    rec.output();
    tri.output();
   
    return 0;
}
