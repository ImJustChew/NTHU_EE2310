#include <iostream>
#include <string>

using namespace std;

bool checksub(int s1[], int s2[], int a, int b, int len) {
    // cout << "Checking " << a << " " << b << endl;
    for(int i = 0; i < len; i++) {
        if(s1[a+i] != s2[b+i]) return false;
    }
    return true;
}

void printsub(int s1[], int a, int len) {
    for(int i = 0; i < len; i++) {
        if(i != 0) cout << " ";
        cout << s1[a + i];
    }
    cout << endl;
}

int lcs(int s1[], int s2[], int j, int k, string mode) {
    int a = 0, b = 0, len = 1, longest = 0;
    while(len != j && len != k) {
        //for each a to a + len in s1, check with b to b + len, if false, a++
        //if a + len == j, then b++, repeat again,
        //if b + len == k, then len++, repeat again,
        //if seq found, set longest, get len, continue
        a = 0;
        while(a + len < j) {
            b = 0;
            while(b + len < k) {
                if(checksub(s1,s2, a, b, len)) {
                    longest = len;
                }
                b++;
            }
            a++;
        }
        len++;
    }
    if(mode == "str") {
        a = 0;
        while(a + longest < j) {
            b = 0;
            while(b + longest < k) {
                if(checksub(s1,s2, a, b, longest)) {
                    printsub(s1, a, longest);
                }
                b++;
            }
            a++;
        }

    }
    return longest;
}

int main() {
    int j,k;
    cin >> j;
    int *s1 = new int[j];
    for (int i = 0; i < j; i++) {
        cin >> s1[i];
    }
    cin >> k;
    int *s2 = new int[k];
    for (int i = 0; i < k; i++) {
        cin >> s2[i];
    }

    string mode;
    cin >> mode;
    int longest = lcs(s1, s2, j, k, mode);
    if(mode == "len") cout << longest << endl;
    
    return 0;
}
