#include <iostream> 
#include <algorithm> 
using namespace std; 
  
// Function to return k'th smallest element in a given array 
int kthSmallest(int arr[], int n, int k) 
{ 
    // Sort the given array 
    sort(arr, arr+n); 
  
    // Return k'th element in the sorted array 
    return arr[k-1]; 
} 
  
// Driver program to test above methods 
int main() 
{ 
    int arr[] = {12, 3, 5, 7, 19}; 
    int n = sizeof(arr)/sizeof(arr[0]), k = 2; 
    cout << "K'th smallest element is " <<  kthSmallest(arr, n, k) << endl ; 
    return 0; 
} 

/* 
Method 1
Sort the given array using a O(N log N) sorting algorithm like Merge Sort,
Heap Sort, etc and return the element at index k-1 in the sorted array.
Time Complexity of this solution is O(N Log N)
*/

/*
Method 2

A simple optomization is to create a Min Heap of the given n elements and call extractMin() k times.
Time complexity of this solution is O(n + kLogn).

*/

/*
Method 3 (Using Max-Heap)
We can also use Max Heap for finding the k’th smallest element. Following is algorithm.
1) Build a Max-Heap MH of the first k elements (arr[0] to arr[k-1]) of the given array. O(k)

2) For each element, after the k’th element (arr[k] to arr[n-1]), compare it with root of MH.
……a) If the element is less than the root then make it root and call heapify for MH
……b) Else ignore it.
// The step 2 is O((n-k)*logk)

3) Finally, root of the MH is the kth smallest element.

Time complexity of this solution is O(k + (n-k)*Logk)

*/
