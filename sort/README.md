## sorting

| algo          | worst-case | best-case  | notes |
| ------------- |-------------| ------------| --------------|
| selection sort   | O(n^2)      | O(n^2)      | |
| bubble sort      | O(n^2)      | O(n)        | approaches O(n) if the list is more sorted |
| insertion sort   | O(n^2)      | O(n)        | approaches O(n) if the list is more sorted |
| quick sort       | O(n^2)      | O(n log n)  | average runtime is O(n log n) with median pivot selection, O(n^2) is with worst possible pivots |
| merge sort       | O(n log n)  | O(n log n)  | |

### selection sort 
- Will run with O(n^2) no matter how sorted the list is already. 
- Iterate through the list and swap the current element with the smallest unsorted element. 

(given `vector<int>& v` is an unsorted list of numbers.) 

```cplusplus
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