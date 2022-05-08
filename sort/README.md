## Sorting algorithms

| algo          | worst-case | best-case  | notes |
| ------------- |-------------| ------------| --------------|
| selection sort   | O(n^2)      | O(n^2)      | |
| bubble sort      | O(n^2)      | O(n)        | approaches O(n) if the list is more sorted |
| insertion sort   | O(n^2)      | O(n)        | approaches O(n) if the list is more sorted |
| quick sort       | O(n^2)      | O(n log n)  | average runtime is O(n log n) with median pivot selection, O(n^2) is with worst possible pivots |
| merge sort       | O(n log n)  | O(n log n)  | |

---

### Selection sort 
- Best and worst runtime: O(n^2), no matter how sorted the list is already. 
- Iterate through the list and swap the current element with the smallest unsorted element. 

(given `vector<int>& v` is an unsorted list of numbers.) 

```c++
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
```

### Bubble sort 
- Worst-case runtime: O(n^2), best-case: O(n) as the initial list approaches sorted. 
- "Bubbles" larger numbers to the front of the list by comparing an element to its immediate next element.
  - If the largest element is the first, it will be taken down the line + used in each comparison in the first run.   
- Unlike selection sort it can improve runtime by stopping if a full run is complete w/o a swap (aka list is sorted). 

```c++
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
```

### Insertion sort 
- Like bubble sort—Worst-case runtime: O(n^2), best-case: O(n) as the initial list approaches sorted. 
- Insertion sort (and bubble sort) are good for nearly-sorted lists. 
- Conceptually sort of opposite bubble sort, but different implementation:
  - Pull the element sorted out of the list, and keep it consistent for the run. 
  - If any previous elements are larger than it, move them up one. 
  - Finally insert the pulled out element back before the last element larger than it. 

(low = 0, high = v.size() - 1 to sort full array)

```c++
void insertion_sort(vector<int>& v, int low, int high) {
    for(int i = low + 1; i <= high; i++) {
        int j = i; 
        int current = v[j]; 

        while(j > low && (v[j - 1] > current)) {
            v[j] = v[j - 1];
            --j;
        }

        v[j] = current; 
    }
}
```

### Quicksort 
- Worst case: O(n^2), if the worst pivot is chosen every time. Average + best case: O(n log n), if the median of 3 method is used.
- Median of three method order is important:
  - mid < low 
  - high < low
  - high < mid   
- Recursive, and base case is sorting chunks of the list (10 items) with insertion sort.
  - i is already sorted, so the upper + lower bounds of the new sub-lists are i - 1 and i + 1, respectively 

```c++
void quicksort(vector<int>& v, int low, int high) {
     if(low + 10 > high) {
        // insertion sort 
        return; 
    }

    int mid = (low + high) / 2;
    if(v[mid] < v[low])
        swap(v[mid], v[low]); 
    if(v[high] < v[low])
        swap(v[high], v[low]);
    if(v[high] < v[mid])
        swap(v[high], v[mid]); 
    
    int pivot = v[mid]; 

    swap(v[mid], v[high - 1]); // hide pivot during sorting

    int i = low; 
    int j = high - 1; 
    while(true) {
        while(v[++i] < pivot) {}
        while(v[--j] >= pivot) {}
        if(i < j)
            swap(v[i], v[j]);
        else
            break; 
    }

    swap(v[i], v[high - 1]); // return pivot to its correct place 
    quicksort(v, low, i - 1);
    quicksort(v, i + 1, high);   
}
```

### merge sort 
- Best and worst case runtime: O(n log n)
- Has a linear space requirement (needs to store copy of itself). 
  - Split the list in sublists until items are atomized. 
  - Merge sublists into one sorted list by iterating through each list and sorting them in a temp array. 
  - Copy the values of temp array into the correct indices in the real array. 
- Another recursive sorting algo 
  - There's usually a helper function split out to merge the two lists—I think it the recursion is clearer when the merge is at the bottom 

```c++
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
```


