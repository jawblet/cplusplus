#include <iostream>
#include <list>
using namespace std; 

class Stack {
    list<int> data;
    public:
        Stack() {}
        void push(int item) { data.push_front(item); }
        void pop() { data.pop_front(); }
        list<int>::iterator begin() { return data.begin(); }
        list<int>::iterator end() { return data.end(); }
        void sort(); 
};

void Stack::sort() {
    list<int>::iterator itr = begin();

    while(itr != end()) {
        cout << *itr << endl;
        itr++;
    }
}

int main() {
    Stack s; 
    s.push(5);
    s.push(3);
    s.push(7);
    s.push(1); 

    s.sort();

    return 0;
}