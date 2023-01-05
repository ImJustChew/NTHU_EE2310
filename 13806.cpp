#include <iostream>

using namespace std;

class Time{
    private:
        int hour, min, sec;
    public:
        Time ();
        Time (int _hour, int _min, int _sec);
        friend istream& operator >> (istream& in, Time& time);
        friend ostream& operator << (ostream& out, const Time& time);
};

Time::Time() {
    hour = 0;
    min = 0;
    sec = 0;
}

Time::Time(int _hour, int _min, int _sec) {
    hour = _hour;
    min = _min;
    sec = _sec;
}

istream& operator >> (istream& in, Time& time) {
    char dummy;
    in >> time.hour >> dummy >> time.min >> dummy >> time.sec;
    return in;
}

ostream& operator << (ostream& out, const Time& time){
    out << time.hour << ":" << time.min << ":" << time.sec;
    return out;
}


int main() {
    Time t1, t2(10, 3, 27);
    cout << t1 << endl << t2 << endl;
    cin >> t1;
    cout << t1<< endl;
    return 0;
}
#include <iostream>

using namespace std;

class Time{
    private:
        int hour, min, sec;
    public:
        Time ();
        Time (int _hour, int _min, int _sec);
        friend istream& operator >> (istream& in, Time& time);
        friend ostream& operator << (ostream& out, const Time& time);
};

Time::Time() {
    hour = 0;
    min = 0;
    sec = 0;
}

Time::Time(int _hour, int _min, int _sec) {
    hour = _hour;
    min = _min;
    sec = _sec;
}

istream& operator >> (istream& in, Time& time) {
    char dummy;
    in >> time.hour >> dummy >> time.min >> dummy >> time.sec;
    return in;
}

ostream& operator << (ostream& out, const Time& time){
    out << time.hour << ":" << time.min << ":" << time.sec;
    return out;
}


int main() {
    Time t1, t2(10, 3, 27);
    cout << t1 << endl << t2 << endl;
    cin >> t1;
    cout << t1<< endl;
    return 0;
}
