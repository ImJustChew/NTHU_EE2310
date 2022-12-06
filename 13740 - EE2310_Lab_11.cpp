#include <iostream>
#include <algorithm>

using namespace std;

#ifndef  FRACTION_H
#define  FRACTION_H

class Fraction {
public:
	void input();
	void display();         // display fraction
	void add(Fraction frac2);  
	void sub(Fraction frac2);  
	void mul(Fraction frac2);  
	void div(Fraction frac2);  

private:
	void reduce();       
  	/* reduce the fraction to simplest form */
	int numer, denom;
};

#endif

void Fraction::input() {
	char temp;
	cin >> numer >> temp >> denom;
}
void Fraction::display(){
	cout << numer << "/" << denom;
}
void Fraction::add(Fraction frac2) {
	numer = numer*frac2.denom + frac2.numer*denom;
	denom = denom*frac2.denom;
	reduce();
}

void Fraction::sub(Fraction frac2) {
	numer = numer*frac2.denom - frac2.numer*denom;
	denom = denom*frac2.denom;
	reduce();
}
void Fraction::mul(Fraction frac2){
	numer = numer*frac2.numer;
	denom = denom*frac2.denom;
	reduce();
} 
void Fraction::div(Fraction frac2){
	if(denom == 0 || frac2.numer == 0 || frac2.denom == 0) {
		cout << "dividing by zero" << endl;
		exit(0);
	}
	numer = numer*frac2.denom;
	denom = denom*frac2.numer;
	reduce();
} 

void Fraction::reduce(){
	int gcdval;
	do {
		gcdval = __gcd(abs(numer), abs(denom));
		if(gcdval != 0) {
			numer /= gcdval;
			denom /= gcdval;
		}
	}
	while(gcdval > 1);
}
int main() {
    Fraction num1, num2, ans;
    char oper;
    num1.input();
    cin >> oper;
    num2.input();
    ans = num1;

    switch (oper) {
      case '+':
        ans.add(num2); break;
      case '-':
        ans.sub(num2); break;
      case '*':
        ans.mul(num2); break;
      case '/':
        ans.div(num2); break;
    }


    // display result
    cout << '(';
    num1.display();
    cout << ") "  << oper << " (";
    num2.display();
    cout << ") = ";
    ans.display();
    cout << endl;

    return 0;
}