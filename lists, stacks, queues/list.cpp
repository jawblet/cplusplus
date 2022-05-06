#include <iostream>
#include <list>
using namespace std;

class LL {
    list<int> data;
    public:
        LL() {};
        void push(int dat) { data.push_back(dat); }
        void pop() { data.pop_front(); }
        int front() { return data.front(); }
        list<int>::iterator get_begin() { return data.begin(); }

};

int main() {

    return 0;
}