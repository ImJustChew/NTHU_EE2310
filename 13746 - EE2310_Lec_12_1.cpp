#include <iostream>
#include <algorithm>

using namespace std;

#ifndef  FRACTION_H
#define  FRACTION_H

class Fraction {
public:
	void input();
	void display();         // display fraction
	friend Fraction add(Fraction frac1, Fraction frac2);  
	friend Fraction sub(Fraction frac1, Fraction frac2);  
	friend Fraction mul(Fraction frac1, Fraction frac2);  
	friend Fraction div(Fraction frac1, Fraction frac2);  

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
Fraction add(Fraction frac1, Fraction frac2) {
    Fraction ans;
	ans.numer = frac1.numer*frac2.denom + frac2.numer*frac1.denom;
	ans.denom = frac1.denom*frac2.denom;
	ans.reduce();
    return ans;
}

Fraction sub(Fraction frac1, Fraction frac2) {
    Fraction ans;
	ans.numer = frac1.numer*frac2.denom - frac2.numer*frac1.denom;
	ans.denom = frac1.denom*frac2.denom;
	ans.reduce();
    return ans;
}
Fraction mul(Fraction frac1, Fraction frac2){
    Fraction ans;
	ans.numer = frac1.numer*frac2.numer;
	ans.denom = frac1.denom*frac2.denom;
	ans.reduce();
    return ans;
} 
Fraction div(Fraction frac1, Fraction frac2){
	if(frac1.denom == 0 || frac2.numer == 0 || frac2.denom == 0) {
		cout << "dividing by zero" << endl;
		exit(0);
	}
    Fraction ans;
	ans.numer = frac1.numer*frac2.denom;
	ans.denom = frac1.denom*frac2.numer;
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
        ans = add(num1, num2); break;
      case '-':
        ans = sub(num1, num2); break;
      case '*':
        ans = mul(num1, num2); break;
      case '/':
        ans = div(num1, num2); break;
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
