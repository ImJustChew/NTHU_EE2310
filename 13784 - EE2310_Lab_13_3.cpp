/*

Modify the class Shape by changing its privated data members to protected data members.
We can remove all 3 member functions get_x(), get_y(), get_color(). Keep the constructor Shape(int, int, string).
Define another member function output() in Shape that simply outputs I'm a shape\n.
The main function is given as follows. Do not change it.
*/

#include <iostream>
#include <string>
using namespace std;

class Shape {
    protected:
        int location_x;
        int location_y;
        string color;
    public:
        Shape(int x, int y, string c);
        virtual void output();
};

Shape::Shape(int x, int y, string c) {
    location_x = x;
    location_y = y;
    color = c;
}

void Shape::output() {
    cout << "I'm a Shape" << endl;
}

class Rectangle: public Shape {
    public:
        Rectangle(int x, int y, string c);
        void output();
};

Rectangle::Rectangle(int x, int y, string c): Shape(x, y, c) {}

//output : I'm a Rectangle: location_x = 10, location_y = 7, color = blue

void Rectangle::output() {
    cout << "I'm a Rectangle: location_x = " << location_x << ", location_y = " << location_y << ", color = " << color << endl;
}

class Triangle: public Shape {
    public:
        Triangle(int x, int y, string c);
        void output();
};

Triangle::Triangle(int x, int y, string c): Shape(x, y, c) {}

//output : I'm a Triangle: location_x = 10, location_y = 5, color = black

void Triangle::output() {
    cout << "I'm a Triangle: location_x = " << location_x << " , location_y = " << location_y << ", color = " << color << endl;
}

// Do NOT CHANGE main()! You may get penalty points.
int main() {
    int x, y;
    string str;
    cin >> x >> y >> str;
    Rectangle rec(x, y, str);
    cin >> x >> y >> str;
    Triangle  tri(x, y, str);

    rec.output();
    tri.output();
    
    Shape *p = &rec;
    p->output();
    p = &tri;
    p->output();
   
    return 0;
}