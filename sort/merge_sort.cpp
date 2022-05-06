#include <iostream>
#include <vector>
#include <ctime>
using namespace std; 

void merge_sort(vector<int>& v, int low, int high); 
void merge_lists(vector<int>& v, int lower_l, int upper_l, int upper_r);

int main() {
    vector<int> v; 

    const int SIZE = 100;
    const int MAX = 1000;

    for(int i = 0; i < SIZE; i++) 
        v.push_back(rand() % MAX + 1); 
    
    merge_sort(v, 0, v.size() - 1);

    for(int i: v) {
        cout << i << " "; 
    }

    return 0; 
}

void merge_sort(vector<int>& v, int low, int high) {
    if(low >= high) {
        return; 
    }

    int mid = (low + high )/ 2;
    merge_sort(v, low, mid);
    merge_sort(v, mid + 1, high);

    merge_lists(v, low, mid, high);
}

void merge_lists(vector<int>& v, int lower_l, int upper_l, int upper_r) {
    int lower_r = upper_l + 1; 

    int i = lower_l; 
    int j = lower_r; 

    vector<int> temp; 

    while(i <= upper_l && j <= upper_r) {
        if(v[i] < v[j]) {
            temp.push_back(v[i]);
            i++; 
        } else { 
            temp.push_back(v[j]);
            j++; 
        }
    }

    while(i <= upper_l) {
        temp.push_back(v[i++]);
    }

    while(j <= upper_r) {
        temp.push_back(v[j++]);
    }

    // copy temp array to real 
    int count = 0; 
    for(int a = lower_l; a <= upper_r; a++) {
        v[a] = temp[count];
        count++; 
    }
}
