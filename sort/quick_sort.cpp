#include <iostream>
#include <vector>
using namespace std; 

const int SIZE = 100;
const int MAX = 1000; 

void quick_sort(vector<int>& v, int low, int high);
void insertion_sort(vector<int>& v, int low, int high);

int main() {
    vector<int> v;
    for(int i = 0; i < SIZE; i++) {
        v.push_back(rand() % MAX + 1);
    }

    quick_sort(v, 0, v.size() - 1);

    for(int i: v)
        cout << i << " "; 

    return 0; 
}

void quick_sort(vector<int>& v, int low, int high) {
    if(low + 10 > high) {
        insertion_sort(v, low, high); 
        return; 
    }

    int mid = (low + high) / 2;

    if(v[low] > v[mid])
        swap(v[low], v[mid]);
    if(v[low] > v[high])
        swap(v[high], v[low]);
    if(v[mid] > v[high])
        swap(v[mid], v[high]); 
    
    int pivot = v[mid];

    swap(v[mid], v[high - 1]);  // move pivot
    
    int i = low; 
    int j = high - 1; 

    while(true) {
        while(v[++i] < pivot) {}
        while(v[--j] > pivot) {}

        if(i < j) {
            swap(v[i], v[j]);
        } else {
            break; 
        }
    }

    swap(v[i], v[high - 1]); 

    quick_sort(v, low, i - 1);
    quick_sort(v, i + 1, high);
}

void insertion_sort(vector<int>& v, int low, int high) {
    for(int i = 0; i < v.size() - 1; i++) {
        int j = i; 

        while(j >= 0 && v[j] > v[j + 1]) {
            swap(v[j], v[j + 1]);
            j--;
        }
    }
}