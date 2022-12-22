#include <iostream>
#include <string>

#define PI 3.14159


using namespace std;

class Shape {
    protected:
        int location_x;
        int location_y;
        string color;
    public:
        Shape(int x, int y, string c);
        virtual void output() = 0;
        virtual double area() = 0;
};

Shape::Shape(int x, int y, string c) {
    location_x = x;
    location_y = y;
    color = c;
}


class Rectangle: public Shape {
    public:
        Rectangle(double w, double h, int x, int y, string c);
        void output();
        double area();
    protected:
        double width, height;
};

Rectangle::Rectangle(double w, double h, int x, int y, string c): Shape(x, y, c) {
    width = w;
    height = h;
}

//cout << blue Rectangle at (10,7)
void Rectangle::output() {
    cout << color << " Rectangle at (" << location_x << "," << location_y << ")" << endl;
}

double Rectangle::area() {
    return width * height;
}

class Triangle: public Shape {
    public:
        Triangle(double b, double h, int x, int y, string c);
        void output();
        double area();
    protected:
        double base, height;
};

Triangle::Triangle(double b, double h, int x, int y, string c): Shape(x, y, c) {
    base = b;
    height = h;
}

void Triangle::output() {
    cout << color << " Triangle at (" << location_x << "," << location_y << ")" << endl;
}

double Triangle::area() {
    return base * height / 2;
}

class Circle : public Shape {
    public:
        Circle(double r, int x, int y, string c);
        void output();
        double area();
    protected:
        double radius;
};

Circle::Circle(double r, int x, int y, string c): Shape(x, y, c) {
    radius = r;
}

void Circle::output() {
    cout << color << " Circle at (" << location_x << "," << location_y << ")" << endl;
}

double Circle::area() {
    return PI * radius * radius;
}

int main() {
    double a, b;
    int x, y; // location of the shape
    string str;
    cin >> a >> b >> x >> y >> str;
    Rectangle rec(a, b, x, y, str);

    cin >> a >> b >> x >> y >> str;
    Triangle  tri(a, b, x, y, str);
    
    cin >> a >> x >> y >> str;
    Circle cir(a, x, y, str);
    
    // polymorphism using pointer
    Shape *ptr = &rec;
    ptr->output();
    cout << ptr->area() << endl;
    ptr = &tri;
    ptr->output();
    cout << ptr->area() << endl;

    // polymorphism using reference
    Shape &s1 = cir;
    s1.output();
    cout << s1.area() << endl;
    
    return 0;
}