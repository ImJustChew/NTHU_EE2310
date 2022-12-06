#include <iostream>
using namespace std;
int days[] = {
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
};

int main()
{
    int m,d;
		char dummy;
		
		cin >> m >> dummy >> d;
    
    if(m > 12 || d > days[m-1] || dummy != '/') {
        cout << "Input Error" << endl;
        return 0;
    }
    
    int daysago = 1;
    for(int i = 1; i < m; i++) {
        daysago += days[i-1];
    }
    daysago += d;
    
    switch(daysago % 7) {
        case 0: cout << "Thursday" << endl; break;
        case 1: cout << "Friday" << endl; break;
        case 2: cout << "Saturday" << endl; break;
        case 3: cout << "Sunday" << endl; break;
        case 4: cout << "Monday" << endl; break;
        case 5: cout << "Tuesday" << endl; break;
        case 6: cout << "Wednesday" << endl; break;
    }

    return 0;
}