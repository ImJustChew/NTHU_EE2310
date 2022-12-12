#include <iostream>
#include <algorithm>

using namespace std;

#ifndef  FRACTION_H
#define  FRACTION_H

class Fraction {
public:
	void input();
	void display();         // display fraction
	Fraction operator +(Fraction frac2);  
	Fraction operator -(Fraction frac2);  
	Fraction operator *(Fraction frac2);  
	Fraction operator /(Fraction frac2);  

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
Fraction Fraction::operator +(Fraction frac2) {
    Fraction ans;
	ans.numer = numer*frac2.denom + frac2.numer*denom;
	ans.denom = denom*frac2.denom;
	ans.reduce();
    return ans;
}

Fraction Fraction::operator -(Fraction frac2) {
    Fraction ans;
	ans.numer = numer*frac2.denom - frac2.numer*denom;
	ans.denom = denom*frac2.denom;
	ans.reduce();
    return ans;
}
Fraction Fraction::operator *(Fraction frac2){
    Fraction ans;
	ans.numer = numer*frac2.numer;
	ans.denom = denom*frac2.denom;
	ans.reduce();
    return ans;
} 
Fraction Fraction::operator /(Fraction frac2){
	if(denom == 0 || frac2.numer == 0 || frac2.denom == 0) {
		cout << "dividing by zero" << endl;
		exit(0);
	}
    Fraction ans;
	ans.numer = numer*frac2.denom;
	ans.denom = denom*frac2.numer;
	ans.reduce();
    return ans;
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

// DO NOT CHANGE main() !!!
int main() {
    Fraction num1, num2, ans;
    char oper;
    num1.input();
    cin >> oper;
    num2.input();

    switch (oper) {
      case '+':
        ans = num1 + num2; break;
      case '-':
        ans = num1 - num2; break;
      case '*':
        ans = num1 * num2; break;
      case '/':
        ans = num1 / num2; break;
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