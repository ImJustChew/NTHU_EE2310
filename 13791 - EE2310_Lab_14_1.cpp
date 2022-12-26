#include <iostream>
#include <string>

#if defined(_WIN32) || defined(__MSDOS__)
   #define SPADE   "\x06"
   #define CLUB    "\x05"
   #define HEART   "\x03"
   #define DIAMOND "\x04"
#else
   #define SPADE   "\xE2\x99\xA0"
   #define CLUB    "\xE2\x99\xA3"
   #define HEART   "\xE2\x99\xA5"
   #define DIAMOND "\xE2\x99\xA6"
#endif

using namespace std;

class Card {
    public:
		friend istream& operator >> (istream& in, Card& c);
		friend ostream& operator << (ostream& out, const Card& c);
		bool operator < (const Card& c);
		bool operator <= (const Card& c);
		bool operator == (const Card& c);
		bool operator > (const Card& c);
		bool operator >= (const Card& c);
    private:
		char suit;
		char face;
};

istream& operator >> (istream& in, Card& c) {
	in >> c.suit >> c.face;
	return in;
}

ostream& operator << (ostream& out, const Card& c) {
	//output the corresponding suit
	switch(c.suit) {
		case 'S':
			out << SPADE;
			break;
		case 'C':
			out << CLUB;
			break;
		case 'H':
			out << HEART;
			break;
		case 'D':
			out << DIAMOND;
			break;
	}
	//output the face
	if(c.face == 'T') {
		out << "10";
	}
	else {
		out << c.face;
	}
	return out;
}

bool Card::operator < (const Card& c) {
	//consder JQK as 11, 12, 13, A as 1, then the suit S > H > D > C
	if (face == c.face) {
		int suit1 = suit == 'S' ? 4 : suit == 'H' ? 3 : suit == 'D' ? 2 : 1;
		int suit2 = c.suit == 'S' ? 4 : c.suit == 'H' ? 3 : c.suit == 'D' ? 2 : 1;

		return suit1 < suit2;
	}
	else {
		int face1 = face == 'J' ? 11 : face == 'Q' ? 12 : face == 'K' ? 13 : face == 'T' ? 10: face == 'A' ? 14 : face - '0';
		int face2 = c.face == 'J' ? 11 : c.face == 'Q' ? 12 : c.face == 'K' ? 13 : face == 'T' ? 10: c.face == 'A' ? 14 : c.face - '0';
		return face1 < face2;
	}
}

bool Card::operator <= (const Card& c) {
	if (face == c.face && suit == c.suit) {
		return true;
	}
	else {
		return *this < c;
	}
}

bool Card::operator == (const Card& c) {
	return suit == c.suit && face == c.face;
}

bool Card::operator > (const Card& c) {
	return !(*this <= c);
}

bool Card::operator >= (const Card& c) {
	return !(*this < c);
}

template <typename T> void MergeSort(T *arr, int begin_pos, int end_pos){
	if(begin_pos < end_pos) {
		int mid = (begin_pos + end_pos) / 2;
		MergeSort(arr, begin_pos, mid);
		MergeSort(arr, mid + 1, end_pos);
		merge(arr, begin_pos, mid, end_pos);
	}
}

template <typename T> void merge(T *arr, int begin_pos, int mid, int end_pos) {
	int i = begin_pos;
	int j = mid + 1;
	int k = 0;
	T *temp = new T[end_pos - begin_pos + 1];
	while(i <= mid && j <= end_pos) {
		if(arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {
			temp[k++] = arr[j++];
		}
	}
	while(i <= mid) {
		temp[k++] = arr[i++];
	}
	while(j <= end_pos) {
		temp[k++] = arr[j++];
	}
	for(int i=0; i< k; i++) {
		arr[begin_pos + i] = temp[i];
	}
	delete [] temp;
}


int main(){
    int size;
    cin >> size;
    Card *a = new Card[size];
    for(int i=0; i< size; i++) {
        cin >> a[i];
    }

    //  sort
    MergeSort<Card>(a, 0, size-1);

    //  output
    for(int i=0; i< size-1; i++) {
        cout << a[i] << ' ';
    }

    cout << a[size - 1] << endl;
    return 0;
}