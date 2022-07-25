#include <iostream>
using namespace std;

class Item {
        int x;
    public:
        Item(int some_x): x(some_x) {};
        int get_x() { return x; }
        void set_x(int some_x) { x = some_x; };
        Item& get_copy() { return *this; }
        Item* get_ptr() { return this; }
};

int main() {
    Item item_1(3);
    Item item_2 = item_1.get_copy();
    Item* item_3 = item_1.get_ptr();

    cout << &item_1 << endl;    // item 1
    cout << &item_2 << endl;    // copy of item 1
    cout << item_3 << endl;     // pointer to item 1 
}

/*
    item_1.set_x(4);
    cout << item_3->get_x() << endl;
    cout << item_2.get_x() << endl; 
*/