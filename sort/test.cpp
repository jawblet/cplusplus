#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

const int SIZE = 100;
const int MAX = 1000; 

void selection_sort(vector<int>& v) {
    for(int i = 0; i < v.size() - 1; i++) {
        int min = v[i];
        int min_index = i;
        for(int j = i + 1; j < v.size(); j++) {
            if(v[j] < min) {
                min = v[j];
                min_index = j;
            }
        }
        int original = v[i];
        v[min_index] = original;
        v[i] = min; 
    }
}

int main() {
    // Make 100-length array of random numbers 1 - 1000 
    vector<int> v; 
    for(int i = 0; i < SIZE; i++) 
        v.push_back(rand() % MAX + 1);
    
    selection_sort(v); 

    // print new order and check if sorted 
    for(int i = 0; i < v.size(); i++) {
       cout << v[i] << " ";

       if(i != 0 && v[i] < v[i - 1]) 
        cout << "\n Error! " << v[i] << " is not < " << v[i - 1] << " \n"; 
   }


    return 0; 
}