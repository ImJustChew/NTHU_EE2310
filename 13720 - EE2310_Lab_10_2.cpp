
#include <iostream>
using namespace std;

char months[][4] = {
	"Jan",
 	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

class DayOfYear{
public:
  void output(); //member func. prototype
  int month;
  int day;
};

void DayOfYear::output(){
 cout << months[month - 1] << " " << day << endl;
}

int main() {
    DayOfYear today, birthday;
    char dummy;
    cin >> today.month >> dummy >> today.day;
    cin >> birthday.month >> dummy>> birthday.day;
  
    cout << "Today is ";
    today.output();
    cout << "Your birthday is ";
    birthday.output();
    if (today.month == birthday.month
        && today.day == birthday.day)
        cout << "Happy birthday!\n";

    return 0;
}

