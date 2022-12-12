#include <iostream>
#include <algorithm>

using namespace std;

#ifndef  FRACTION_H
#define  FRACTION_H

class Fraction {
public:
    friend ostream& operator <<(ostream& out, Fraction &frac);
    friend istream& operator >>(istream& out, Fraction &frac);
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

ostream& operator <<(ostream& out, Fraction &frac){
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
    cin >> num1 >> oper >> num2;

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

    cout << '(' << num1 << ") " << oper << " (" << num2 << ") = "
         << ans << endl;
    return 0;
}