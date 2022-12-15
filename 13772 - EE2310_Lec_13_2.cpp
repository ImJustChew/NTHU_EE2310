#include <iostream>
#include <algorithm>

using namespace std;

class Node {
    private:
        int data;
        Node *next;
    public:
        friend class Linked_list;
};

class Linked_list {
    private:
        Node *head;
        Node *tail;
    public:
        Linked_list();
        void add_node(int data);
        void reverse();
        void output();
};

Linked_list::Linked_list() {
    head = NULL;
    tail = NULL;
}

void Linked_list::add_node(int data) {
    Node *new_node = new Node();
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

void Linked_list::reverse() {
    Node *current = head;
    Node *prev = NULL;
    Node *next = NULL;
    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void Linked_list::output() {
    Node *current = head;
    int is_first = 1;
    while(current != NULL) {
        cout << (is_first ? "" : " ") << current->data;
        is_first = 0;
        current = current->next;
    }
    cout << endl;
}

int main(){
    Linked_list my_list;
    
    int data, input_size;
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
