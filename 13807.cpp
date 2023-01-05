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
        bool operator < (const Time& time);
        bool operator <= (const Time& time);
        bool operator == (const Time& time);
        bool operator >= (const Time& time);
        bool operator > (const Time& time);
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

bool Time::operator == (const Time& time) {
    return time.hour == hour && time.min == min && time.sec == sec;
}

bool Time::operator < (const Time& time) {
    return (hour < time.hour) || (hour == time.hour && min < time.min) || (hour == time.hour && min == time.min && sec < time.sec);
}

bool Time::operator <= (const Time& time) {
    if(time.hour == hour && time.min == min && time.sec == sec) return true;
    return (hour < time.hour) || (hour == time.hour && min < time.min) || (hour == time.hour && min == time.min && sec < time.sec);
}

bool Time::operator > (const Time& time) {
    return (hour > time.hour) || (hour == time.hour && min > time.min) || (hour == time.hour && min == time.min && sec > time.sec);
}

bool Time::operator >= (const Time& time) {
    if(time.hour == hour && time.min == min && time.sec == sec) return true;
    return (hour > time.hour) || (hour == time.hour && min > time.min) || (hour == time.hour && min == time.min && sec > time.sec);
}


template <class T> 
int partition(T arr[], int start, int end) {
    T pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if(arr[i] <= pivot) {
            count ++;
        }
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;
    while(i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}

template <class T>
void quickSort(T arr[], int start, int end) {
    if(start >= end) return;
    int p = partition(arr, start, end);
    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}


int main() {
    int n;
    cin >> n;
    Time *time = new Time[n];
    for (int i = 0; i < n; i++) {
        cin >> time[i];
    }
    quickSort(time, 0, n-1);
    for (int i = 0; i < n; i++) {
        if(i != 0) cout << " ";
        cout << time[i];
    }

    cout << endl;
}
//4:20:38 4:26:0 3:49:9 9:34:01 5:13:58 3:49:22