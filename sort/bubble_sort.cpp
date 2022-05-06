#include <iostream>
#include <vector>
using namespace std;

void bubble_sort(vector<int>& v);

int main() {
    vector<int> v {40, 21, 0, 1, 2, 44, 7};

    bubble_sort(v);

    for(int i: v)
        cout << i << " "; 

    return 0;
}

void bubble_sort(vector<int>& v) {
    for(int i = 0; i < v.size() - 1; i++) {
        bool swapped = false;

        for(int j = 0; j < v.size() - i - 1; j++) {
            if(v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                swapped = true;
            }
        } 

        if(!swapped)
            break;
    }
}
