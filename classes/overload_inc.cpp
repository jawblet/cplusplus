#include <iostream>
#include <string> 
using namespace std; 

class Inventory {
    string name; 
    int stock; 
    public:
        Inventory(string n, int s): name(n), stock(s) {}
        friend ostream& operator <<(ostream& outs, const Inventory& inv);

        // Increment operators:
        Inventory& operator ++();    
        Inventory operator ++(int);   
};

// Pre-increment 
// returns object reference 
Inventory& Inventory::operator++() {
    stock += 1; 
    return *this;
}

// Post-increment 
// has an empty int param (remember int comes after)
Inventory Inventory::operator++(int) {
    Inventory temp = *this;
    stock += 1; 
    return temp; 
}

ostream& operator <<(ostream& outs, const Inventory& inv) {
    outs << inv.name << " " << inv.stock; 
    return outs;
}

int main() {
    Inventory chair("Desk chair", 5); 
    cout << chair++ << endl;    // 5
    cout << ++chair << endl;    // 7
    return 0; 
}