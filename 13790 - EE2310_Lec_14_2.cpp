#include <iostream>
#include <string>

using namespace std;

template <typename T> T GetMax (T a, T b) {
    return a > b ? a : b;
}

int main () { // DO NOT CHANGE MAIN!!
    int i, j;
    double l, m;
    string s1, s2;
    cin >> i >> j >> l >> m >> s1 >> s2;
    cout << GetMax(i, j) << endl << GetMax(l, m) << endl
         << GetMax<string>(s1, s2) << endl;
    return 0;
}
