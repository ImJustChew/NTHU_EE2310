#include <iostream>

using namespace std;

class Time{
    protected:
        int hour, min, sec;
    public:
        Time ();
        Time (int _hour, int _min, int _sec);
        virtual void output();
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


void Time::output (){
    cout << hour << ":" << min << ":" << sec;
}


class GlobalTime: Time{
    protected:
        int offset;
    public:
        GlobalTime ();
        GlobalTime (int _hour, int _min, int _sec, int _offset);
        friend istream& operator >> (istream& in, GlobalTime& gt);
        friend ostream& operator << (ostream& out, const GlobalTime& gt);
        void output();
};

GlobalTime::GlobalTime() : Time() {
    offset = 0;
}

GlobalTime::GlobalTime(int _hour, int _min, int _sec, int _offset): Time(_hour, _min, _sec) {
    offset = _offset;
}

istream& operator >> (istream& in, GlobalTime& gt) {
    char dummy;
    in >> gt.hour >> dummy >> gt.min >> dummy >> gt.sec >> dummy >> gt.offset;
    if(dummy == '-') gt.offset = -gt.offset;
    return in;
}

ostream& operator << (ostream& out, const GlobalTime& gt){
    out << gt.hour << ":" << gt.min << ":" << gt.sec << (gt.offset >= 0 ? '+': '-') << abs(gt.offset);
    return out;
}

void GlobalTime::output (){
    cout << hour << ":" << min << ":" << sec << (offset >= 0 ? '+': '-') << abs(offset);
}


int main() { // DO NOT CHANGE MAIN !!!
    GlobalTime gt1(10, 3, 27, 3), gt2;
    cin >> gt2;
    Time &t1 = gt1;
    t1.output();
    cout << endl;
    Time &t2 = gt2;
    t2.output();
    cout << endl;
    return 0;
}
