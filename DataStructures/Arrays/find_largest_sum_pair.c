#include <stdio.h>

int findLargestSumPair (int arr[], int n) {
    if (!arr || n<2) return 0;
    
    int first = arr[0] > arr[1] ? arr[0]: arr[1];
    int second = arr[0] < arr[1] ? arr[0]: arr[1];

    int i;

    for (i = 2; i < n; i++) {
        if (arr[i] > second) {
            second = arr[i] > first ? first : arr[i];
            first = arr[i] < first ? first : arr[i];
        }
    }
    return first+second;
}

int main()
{
    int arr[] = {12, 34, 10, 6, 40};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Max Pair Sum is %d\n", findLargestSumPair(arr, n));

    return 0;
}
