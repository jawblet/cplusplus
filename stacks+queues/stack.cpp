#include <iostream>
#include <list> 
#include <ctime>
using namespace std;

template <class T> 
class Stack {
    list<T> data; 
    public:
        Stack() {}
        T front() { return *data.front(); }
        T back() { return *data.back(); }
        typename list<T>::iterator get_begin() { return data.begin(); }
        typename list<T>::iterator get_end() { return data.end(); } 
        void push(T item) { data.push_front(item); }
        T pop();
        bool is_empty() { return data.empty(); }
        int size() { return data.size(); }
        void clear() { data.clear(); }
        void bubble_sort(); 
        void assign(T data);
};

template <class T> 
T Stack<T>::pop() {
    T return_val = data.front(); 
    data.pop_front(); 
    return return_val; 
}

// bubble sort 
template <class T>
void Stack<T>::bubble_sort() {
    typename list<T>::iterator a = get_begin(); 

    while(a++ != get_end()) {
        bool swapped = false;

        typename list<T>::iterator e = get_end();
        typename list<T>::iterator b = get_begin();
        typename list<T>::iterator c = get_begin();
        c++; 

        while(c != e) {
            cout << *b << " " << *c << endl;
           if(*b > *c) {
                swap(*b, *c);
                swapped = true; 
            } 
            b++;
            c++; 
        } 

         if(!swapped) {
                break; 
            }
    }
} 

int main() {
    Stack<int> stack; 

    for(int i = 0; i < 10; i++) {
        stack.push(rand() % 100 + 1);
    }

    list<int>::iterator u_it = stack.get_begin(); 
    while(u_it != stack.get_end()) {
        cout << *u_it << " ";
        u_it++; 
    }

    cout << "\nsorted: " << endl; 
    stack.bubble_sort();

    list<int>::iterator it = stack.get_begin(); 
    while(it != stack.get_end()) {
        cout << *it << " ";
        it++; 
    }


    return 0; 
}

      /*  typename list<T>::iterator b = get_begin(); 
        for(++b; b != get_end(); ++b) {
            cout << *--b << " " << *b << endl;
           if(*--b > *b) {
                this->swap(--b, b);
                swapped = true; 
            } */