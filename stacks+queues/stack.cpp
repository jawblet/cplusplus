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
        void swap(T item1, T item2) { swap(item1, item2); }
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
// move larger numbers forward 
template <class T>
void Stack<T>::bubble_sort() {
    typename list<T>::iterator a = get_begin(); 

    bool swapped = false;

    while(a != get_end()) {
        typename list<T>::iterator b = get_begin();
        for(b++; b != get_end(); b++) {
           
            T a_value = *a;
            T b_value = *b;
            cout << a_value << " "<< b_value  << endl; 

            if(a_value > b_value) {
                swap(a_value, b_value);
                swapped = true; 
            }
        }
        if(!swapped)
            break; 
        a++; 
    }
} 

int main() {
    Stack<int> stack; 

    for(int i = 0; i < 10; i++) {
        stack.push(rand() % 100 + 1);
    }

    list<int>::iterator it = stack.get_begin()++; 

    while(it != stack.get_end()) {
        cout << *it++ << endl;
    }

    cout << "\nsorted: " << endl; 
    stack.bubble_sort();

    while(it != stack.get_end()) {
        cout << *it++ << endl;
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