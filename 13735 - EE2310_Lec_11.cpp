/* Redo Lab 8-1 using class*/

/* All data members MUST BE PRIVATE */

/* Do not change main */

 

#include <iostream>
#define MAX_NEG -1000000000
using namespace std;

class stack_arr_t {
public:
/*
 * Must include the constructor, dynamic_push, dynamic_pop, and show functions.
 */
	stack_arr_t(int size);
	~stack_arr_t();
	void show();
	void dynamic_push(int elem);
	int dynamic_pop();
private:
	int *head;
	int top;
	int max_size;
};

/*
 * Member function definitions should be put here!! Add stack_arr_t:: to their names.
 * Constructor's name must be the same as the class name. Do not specify any return type for the constructor!
 */

stack_arr_t::stack_arr_t(int size) {
	head = new int(size);
	top = 0;
	max_size = size;
}

stack_arr_t::~stack_arr_t() {
	delete [] head;
}

void stack_arr_t::show() {
	if(top == 0) cout << "Stack empty!" << endl;
	else {
		cout << "Stack contains " << top << " element(s)" << endl;
		for(int i=0; i< top - 1; ++i) {
				cout << head[i] << " " ;
		}
		cout << head[top - 1] << endl;
	}
   cout << "top = " << top << ", max_size = " << max_size << endl;
}

void stack_arr_t::dynamic_push(int elem) {
	if(top == max_size) {
		max_size = max_size * 2;
		int *new_array = new int(max_size);
		for(int i = 0; i < (max_size/2); i++) {
			new_array[i] = head[i];
		}
		delete [] head;
		head = new_array;
	}
	head[top++] = elem;
}
 
int stack_arr_t::dynamic_pop() {
	if(top <= max_size/4) {
		max_size = max_size/2;
		int *new_array = new int(max_size);
		for(int i = 0; i < max_size; i++) {
			new_array[i] = head[i];
		}
		delete [] head;
		head = new_array;
	}
	return head[--top];
}
 

/* Do not change main()!! Penalty points may be applied !!
 * 請勿改 main，否則可能被扣分！！
 */
int main(){
    
    int input_size, temp, max_size, pop_size;

    /* input stack's max size */
    cin >> max_size;
    
    /* constructor will be called here */
    stack_arr_t my_stack(max_size);


    /* input elements to be pushed */
    cin >> input_size;
    int i;
    for(i=0; i<input_size; ++i){
        cin >> temp;
        my_stack.dynamic_push(temp);
    }

    /* input number of elements to be popped */
    cin >> pop_size;
    for(i=0; i < pop_size-1; ++i){
        cout << my_stack.dynamic_pop() << ' ';
    }
    if (0 != pop_size){
        cout << my_stack.dynamic_pop() << endl;
    }

    my_stack.show();

    return 0;
}

