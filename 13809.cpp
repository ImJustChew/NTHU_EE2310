// Given two sequences s1 and s2 (of any type). Find their longest common subsequence(s) (LCS). 
// For example, let 
// s1 = {3, 6, 5, 7, 7, 1, 4, 8} and 
// s2 = {4, 45, 7, 7, 1, 9, 3, 6}. 
// Their LCS is {7, 7, 1} of length 3. 
// Implement this function as a template that works on any class T, a
// nd call your function template with int. The I/O format is as follows.

// Input an integer indicating the length of the sequence.
// Each element of a sequence is separated by a whitespace.
// The user first inputs two sequences. Then s/he inputs a mode as follows.
// If mode is len then your program should only output the length of the LCS.
// If mode is seq then your program should output all LCSs. If there are more than one, then your program should output them in lexicographic order.
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

int lcs(int s1[], int s2[], int j, int k) {
    int a = 0, b = 0, len = 1, longest = 0;
    while(len != j && len != k) {
        //for each a to a + len in s1, check with b to b + len, if false, a++
        //if a + len == j, then b++, repeat again,
        //if b + len == k, then len++, repeat again,
        //if seq found, set longest, get len, continue
        a = 0;
        while(a + len < j) {
            b = 0;
            while(b + len < j) {
                if(checksub(s1,s2, a, b, len)) {
                    longest = len;
                }
                b++;
            }
            a++;
        }
        len++;
    }
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

    cout << lcs(s1,s2,j,k) << endl;
    
}
