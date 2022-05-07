#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void quick_sort(vector<int>& v, int low, int high); 
void insertion_sort(vector<int>& v, int low, int high);

const int SIZE = 100;
const int MAX = 1000; 

int main() {
    vector<int> v; 
    for(int i = 0; i < SIZE; i++) 
        v.push_back(rand() % MAX + 1);
    
    quick_sort(v, 0, v.size() - 1);

    for(int i = 0; i < v.size(); i++) {
       cout << v[i] << " ";

       if(i != 0 && v[i] < v[i - 1]) 
        cout << "\n Error! " << v[i] << " is not < " << v[i - 1] << " \n"; 
   }

    return 0;
}
 
void quick_sort(vector<int>& v, int low, int high) {
    if(low + 10 > high) {
        insertion_sort(v, low, high); 
        return;
    }
        

    // get pivot value + sort 3 points 
    int mid = (low + high) / 2; 
    if(v[mid] < v[low]) 
        swap(v[mid], v[low]);
    if(v[high] < v[low])
        swap(v[high], v[low]);
    if(v[high] < v[mid]) 
        swap(v[high], v[mid]); 
    
    int pivot = v[mid]; 

    // swap out pivot
    swap(v[mid], v[high - 1]); 

    // sort around pivot 
    int i = low; 
    int j = high - 1;

    while(true) {
        while(v[++i] < pivot) {}
        while(v[--j] > pivot) {}
        if(i < j)
            swap(v[i], v[j]); 
        else
            break; 
    }

    // swap pivot back in 
    swap(v[i], v[high - 1]);

    // i is sorted already, avoid passing it again 
    quick_sort(v, low, i - 1);
    quick_sort(v, i + 1, high); 
}

void insertion_sort(vector<int>& v, int low, int high) {
    for(int i = low + 1; i <= high; i++) {
        int j = i;
        int current = v[j]; 

        while(j > low && v[j - 1] > current) {
            v[j] = v[j - 1];
            j--; 
        }

        v[j] = current;
    }
}