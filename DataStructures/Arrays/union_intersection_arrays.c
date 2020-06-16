
/*

Given two unsorted arrays that represent two sets (elements in every
array are distinct), find union and intersection of two arrays.

For example, if the input arrays are:
arr1[] = {7, 1, 5, 2, 3, 6}
arr2[] = {3, 8, 6, 20, 7}

Then your program should print Union as {1, 2, 3, 5, 6, 7, 8, 20} and
Intersection as {3, 6}. Note that the elements of union and
intersection can be printed in any order.

*/


/*

Method 1

1. sizeof union array = sizeof arr1 + sizeof arr2
2. copy arr1 to Union array.
3. for each elem in arr2
       if !found in union, add element

O(m.n)


Method 2 : sort smaller array and search big array linear 

a)
1. sort smaller array O(mlogm)
union =  small array
intersection =  empty array
2. for each element in bigger array  O(n)
       search in sorted smaller array.O(logm)
       for union : if not found, add to union
       for intersection : if found, add to intersection array.

This step is n*logm

total running time : O(mlogm) + O(nlogm) = O((m+n)logm)

b)
We could also sort the bigger set first and then search each element in smaller set with sorted bigger set. => O((m+n)log n)
Note that for m < n, log m < log n

So sorting smaller set is a better algo than sorting bigger set.

c)
Sort both : mlogm (sort smaller) + nlogn (sort bigger) + n + m
since m < n => m+n < 2n
=> (m+n)logm < nlogn
method a) is the best.


Method 3: Use hashing O(m+n)
Put array m in hash. 
for each element in n
        if found in hash => intersection
        if !found in hash => union

*/

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static void print_array (int arr[], int size, char *str) {
    printf("\n%s ::::\n", str);
    int i=0;
    for (i=0; i<size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

static bool linear_search (int *arr, int sz, int elem) {
    int i;
    
    for (i=0; i<sz; i++) {
        if (arr[i] > elem) {
            return false;
        }
        if (arr[i] == elem) {
            return true;
        }
    }

    return false;
}

static bool binary_search (int *arr, int sz, int elem) {
    int low, mid, high;
    low = 0;
    high = sz-1;
    
    while (low<=high) {
        mid = (high+low)/2;
        if (arr[mid] == elem) 
            return true;
        
        if (arr[mid] > elem) {
            high = mid-1;
            continue;
        }
        low = mid+1;
    }

    return false;
}

static bool search (int *arr, int sz, int elem) {
    //return linear_search(arr, sz, elem);
    return binary_search(arr, sz, elem);
}


/* O(n.n)
 */
static void bubble_sort (int a[], int sz) {
    int i, j;
    for (i=0; i< sz; i++) {
        for (j=i+1; j<sz; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

static void sort (int arr[], int sz) {
    bubble_sort(arr, sz);
    print_array(arr, sz, "sorted array");
}

static void 
get_intesection (int *arr1, int sz1, int *arr2, int sz2, 
                 int *arr_i, int sz_i) {

    memset(arr_i, 0, sz_i * sizeof arr_i[0]);
    sort(arr1, sz1);

    int i, j = 0;
    for (i = 0; i < sz2; i++) {
        if (search(arr1, sz1, arr2[i])) {
            arr_i[j++] = arr2[i];
        }
    }
}

static void 
get_union (int *arr1, int sz1, int *arr2, int sz2, int *arr_u, int sz_u) {

    memset(arr_u, 0, sz_u * sizeof arr_u[0]);

    sort(arr1, sz1);

    memcpy(arr_u, arr1, sz1 * sizeof arr1[0]);

    int i, j = sz1;

    for (i = 0; i < sz2; i++) {
        if (!search(arr1, sz1, arr2[i])) {
            assert(j < sz_u);
            arr_u[j++] = arr2[i];
        }
    }
}
   
int main (void) {
    int arr1[]  = { 60, 70, 10, 50, 40, 30, 20, 100, 200 };
    int arr2[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };

    int sz1 = sizeof arr1/ sizeof arr1[0];
    int sz2 = sizeof arr2/ sizeof arr2[0];

    int sz_u =  sz1 + sz2;
    int sz_i = sz1 > sz2 ? sz2 : sz1;

    int *arr_u = malloc(sizeof arr1[0] * sz_u);

    if (!arr_u) { 
        printf("Malloc failed for arr_u");
        return -1;
    }
    int *arr_i = malloc(sizeof arr1[0] * sz_i);

    if (!arr_i) { 
        printf("Malloc failed for arr_i");
        free(arr_u);
        return -1;
    }
    
    if (sz1 < sz2) {
        get_intesection(arr1, sz1, arr2, sz2, arr_i, sz_i);
        get_union(arr1, sz1, arr2, sz2, arr_u, sz_u);
    } else {
        get_intesection(arr2, sz2, arr1, sz1, arr_i, sz_i);
        get_union(arr2, sz2, arr1, sz1, arr_u, sz_u);
    }
    
    print_array(arr_u, sz_u, "union array");
    print_array(arr_i, sz_i, "intersection array");
              
}
