#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// Example of sorting around a pivot that is used in quicksort 

int sort(vector<int>& v);

int main() {
    vector<int> v;
    const int size = 5; 
    const int MAX = 1000; 

    for(int i = 0; i < size; i++) {
        v.push_back(rand() % MAX + 1);
    }

    int pivot = sort(v); 
    
    for(int i = 0; i < v.size(); i++) {
         if(v[i] == pivot)
            cout << "\n Pivot:" << v[i] << "\n";
        else  
            cout << v[i] << " ";
    }
    
    return 0;
}

int sort(vector<int>& v) {
    int i = 0; 
    int j = v.size() - 1;

    int pivot = v[0]; // Chosen at random -- bad practice

    while(i < j) {
        while(v[i] <= pivot)
            i++;
        
        while(v[j] > pivot) 
            j--;
        
        if(i < j) {
            swap(v[i++], v[j++]);
        }
    } 
    swap(v[0], v[i - 1]);

    return pivot; 
}
