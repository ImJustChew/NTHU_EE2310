#include <iostream>
#include <algorithm>

using namespace std;


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

class Card {
    public:
        Card ();
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

Card::Card() {
    suit = 'S';
    face = 'A';
}

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

template <class T>
class Linked_list;

template <class T>
class Node {
    private:
        T data;
        Node<T> *next;
    public:
        friend class Linked_list<T>;
};


template <class T>
class Linked_list {
    private:
        Node<T> *head;
        Node<T> *tail;
    public:
        Linked_list();
        void add_node(T data);
        void reverse();
        void output();
};

template <class T>
Linked_list<T>::Linked_list() {
    head = NULL;
    tail = NULL;
}

template <class T>
void Linked_list<T>::add_node(T data) {
    Node<T> *new_node = new Node<T>();
    new_node->data = data;
    new_node->next = NULL;
    if(head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

template <class T>
void Linked_list<T>::reverse() {
    Node<T> *current = head;
    Node<T> *prev = NULL;
    Node<T> *next = NULL;
    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

template <class T>
void Linked_list<T>::output() {
    Node<T> *current = head;
    int is_first = 1;
    while(current != NULL) {
        cout << (is_first ? "" : " ") << current->data;
        is_first = 0;
        current = current->next;
    }
    cout << endl;
}

int main(){
    Linked_list<Card> my_list;
    
    int input_size;
    Card data;
    /* when you add a node, you add it at the tail */
    
    cin >> input_size;
    
    for(int i=0; i < input_size; ++i) {
        cin >> data;
        my_list.add_node(data);
    }
    my_list.output();
    my_list.reverse();
    my_list.output();
    
    return 0;
}
