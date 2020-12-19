#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

static void print_array (int arr[], int sz) {
    int i;
    for (i=0; i<sz; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* O(n^2) */
void bubble_sort (int arr[], int sz) {
    int i, j;

    for (i=0; i<sz-1; i++){
        for (j=i+1; j<sz; j++) {
            if (arr[i] > arr[j]) {
                int swap = arr[i];
                arr[i] = arr[j];
                arr[j] = swap;
            }
        }
    }
    print_array(arr, sz);
}

void sort (int arr[], int sz) {
    bubble_sort(arr, sz);
}

int isSumPossible_3  (int len, int arr[], int sum) {

    sort(arr, len);

    int l = 0;
    int r = len -1;

    while (l < r){
        int add = arr[l] + arr[r];
        if (add == sum) {
            printf("%s: (%d, %d) = %d\n", __FUNCTION__, arr[l], arr[r], sum);
            return 1;
        }
        if (add < sum) 
            l++;
        if (add > sum)
            r--;
    }
    return 0;
}

int isSumPossible_2  (int len, int arr[], int sum) {

    sort(arr, len);

    int i = 0;
    int j = len -1;

    while ( i < j){
        while ((arr[i] + arr[j]) <= sum && i < j) {
            if ((arr[i] + arr[j]) == sum) {
                printf("%s: (%d, %d) = %d\n", __FUNCTION__, 
                       arr[i], arr[j], sum);
                return 1;
            }
            i++;
        }
        j--;
        while ((arr[i] + arr[j]) >= sum && i < j) {
            if ((arr[i] + arr[j]) == sum) {
                printf("%s: (%d, %d) = %d\n", __FUNCTION__, 
                       arr[i], arr[j], sum);
                return 1;
            }
            j--;
        }
    }
    return 0;
}

int isSumPossible (int a_size, int* a, int N) {
    if (!a || (a_size<=0)) {
        return 0;
    }

    //bubble_sort(a, a_size);

    int i, j;

    for (i = 0; i < a_size-1; i++) {
        for (j = i+1; j < a_size; j++) {
            if (a[i]+a[j] == N) 
                return 1;
        }
    }
    return 0;
}

int main() {
    int array[] = { 4, 3, 34, 5 , 14, 1, 13, 7};;
    
    int res, sz = sizeof array/ sizeof array[0];

    int N = 48;

    res = isSumPossible(sz, array, N);
    printf("%d\n", res);

    res = isSumPossible_2(sz, array, N);

    res = isSumPossible_3(sz, array, N);
    return 0;
}
