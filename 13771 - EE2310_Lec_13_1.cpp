#include <iostream>
#include <algorithm>

using namespace std;

#ifndef  FRACTION_H
#define  FRACTION_H

class Fraction {
public:
    Fraction(int n);
    Fraction();
    friend ostream& operator <<(ostream& out, const Fraction &frac);
    friend istream& operator >>(istream& out, Fraction &frac);
	Fraction operator +(Fraction frac2);  
	Fraction operator -(Fraction frac2);  
	Fraction operator *(Fraction frac2);  
	Fraction operator /(Fraction frac2);  
    operator double();

private:
	void reduce();       
  	/* reduce the fraction to simplest form */
	int numer, denom;
};

#endif

Fraction::Fraction(int n) {
    numer = n;
    denom = 1;
}

Fraction::Fraction() {
    numer = 0;
    denom = 1;
}

ostream& operator <<(ostream& out, const Fraction &frac){
    out << frac.numer << "/" << frac.denom;
    return out;
}
istream& operator >>(istream& in, Fraction &frac){
	char temp;
	in >> frac.numer >> temp >> frac.denom;
    return in;
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

Fraction::operator double() {
    return (double)numer/(double)denom;
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
    Fraction num1, num2;
    double x;
    int y;
    char oper1, oper2;
    cin >> num1 >> oper1 >> x;
    cin.ignore(1024, ',');
    cin >> y >> oper2 >> num2;

    switch (oper1) {
      case '+':
        cout << '(' << num1 << ") + (" << x << ") = "<< (double)num1 + x << endl; break;
      case '-':
        cout << '(' << num1 << ") - (" << x << ") = "<< (double)num1 - x << endl; break;
      case '*':
        cout << '(' << num1 << ") * (" << x << ") = "<< (double)num1 * x << endl; break;
      case '/':
        cout << '(' << num1 << ") / (" << x << ") = "<< (double)num1 / x << endl; break;
    }

    switch (oper2) {
      case '+':
        cout << '(' << y << ") + (" << num2 << ") = "<< (Fraction)y + num2 << endl; break;
      case '-':
        cout << '(' << y << ") - (" << num2 << ") = "<< (Fraction)y - num2 << endl; break;
      case '*':
        cout << '(' << y << ") * (" << num2 << ") = "<< (Fraction)y * num2 << endl; break;
      case '/':
        cout << '(' << y << ") / (" << num2 << ") = "<< (Fraction)y / num2 << endl; break;
    }
    return 0;
}
