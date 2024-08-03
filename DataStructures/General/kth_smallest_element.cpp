#include <iostream> 
#include <algorithm> 
using namespace std; 
  
/* 
    Method 1
    Sort the given array using a O(N log N) sorting algorithm like Merge Sort,
    Heap Sort, etc and return the element at index k-1 in the sorted array.
    Time Complexity of this solution is O(N Log N)
*/

// Function to return k'th smallest element in a given array 
int kthSmallest_sort(int arr[], int n, int k) { 
    sort(arr, arr+n); 
  
    // Return k'th element in the sorted array 
    return arr[k-1]; 
}

/*
    Method 2

    A simple optimization is to create a Min Heap of the given n elements and call extractMin() k times.
    Time complexity: O(n * log n + k * log n)
    Space complexity: O(n)

*/
#include <queue>
int kthSmallest_minHeap(int arr[], int n, int k) { 
    priority_queue <int, vector<int>, greater <int> > minHeap;

    while (n) {
        minHeap.push(arr[n--]);
    }
    int ret = INT_MIN;
    while (k--) {
        ret = minHeap.top();
        minHeap.pop();
    }
    return ret;
}

/*
    Method 3 (Using Max-Heap)
    We can also use Max Heap for finding the k’th smallest element. 
    
    Following is algorithm.
    1) Build a Max-Heap MH of the first k elements (arr[0] to arr[k-1]) of the given array. O(k * log k)

    2) For each element, after the k’th element (arr[k] to arr[n-1]), compare it with root of MH.
    ……a) If the element is less than the root then make it root and call heapify for MH
    ……b) Else ignore it.
    // The step 2 is O((n-k)*logk)

    3) Finally, root of the MH is the kth smallest element.

    Time complexity: O(n * logk)
    Space complexity: O(k)
*/

int kthSmallest_maxHeap(int arr[], int n, int k) { 
    priority_queue <int> maxHeap;

    for (auto i = 0; i < n; i++) {
        if (i < k) {
            maxHeap.push(arr[i]);
            continue;
        }
        if (arr[i] > maxHeap.top()) {
            continue;
        }
        maxHeap.push(arr[i]);
        maxHeap.pop();
    }
    
    return maxHeap.top();
}

void test (int arr[], int n, int k) {
    cout << "With Sorting: K'th smallest element is " <<  kthSmallest_sort(arr, n, k) << endl ; 
    cout << "With min heap (Priority queue): K'th smallest element is " <<  kthSmallest_minHeap(arr, n, k) << endl ; 
    cout << "With max heap (Priority queue): K'th smallest element is " <<  kthSmallest_maxHeap(arr, n, k) << endl ; 

}

int main() { 
    int arr[] = {12, 3, 5, 7, 19}; 
    int n = sizeof(arr)/sizeof(arr[0]), k = 2; 
    test(arr, n, k);
    return 0; 
} 