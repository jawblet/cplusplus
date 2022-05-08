#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

const int SIZE = 100;
const int MAX = 1000; 

void merge_sort(vector<int>& v, int low, int high) {
    if(low >= high) {
        return; 
    }

    int mid = (low + high) / 2; 
    merge_sort(v, low, mid); 
    merge_sort(v, mid + 1, high); 

    int lower_l = low, upper_l = mid; 
    int lower_r = mid + 1, upper_r = high;

    int i = lower_l;
    int j = lower_r; 
    vector<int> temp; 

    while(i <= upper_l && j <= upper_r) {
        if(v[i] > v[j]) {
            temp.push_back(v[j]);
            j++;
        } else {
            temp.push_back(v[i]);
            i++;
        }
    }

    // push remainder of either half to the temp array
    for(; i <= upper_l; i++) {
        temp.push_back(v[i]);
    }

    for(; j <= upper_r; j++) {
        temp.push_back(v[j]);
    }

    // copy temp array to real array 
    int count = 0; 
    for(int k = lower_l; k <= upper_r; k++) {
        v[k] = temp[count];
        count++; 
    }
}

int main() {
    // Make 100-length array of random numbers 1 - 1000 
    vector<int> v; 
    for(int i = 0; i < SIZE; i++) 
        v.push_back(rand() % MAX + 1);
    
    // sort 
    merge_sort(v, 0, v.size() - 1); 

    // print new order and check if sorted 
    for(int i = 0; i < v.size(); i++) {
       cout << v[i] << " ";

       if(i != 0 && v[i] < v[i - 1]) 
        cout << "\n Error! " << v[i] << " is not < " << v[i - 1] << " \n"; 
   }


    return 0; 
}

/*
 
    */