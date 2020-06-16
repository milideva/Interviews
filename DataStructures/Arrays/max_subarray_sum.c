#include <stdio.h>

int max (int a, int b) {
    if (a > b) return a;
    return b;
}

// O(n^3)
int max_subarray_sum_1 (int arr[], int n) {
    int best = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i;  j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += arr[k];
            }
            best = max(sum, best);
        }
    }
    return best;
}

// O(n^2)
int max_subarray_sum_2 (int arr[], int n) {
    int best = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i;  j < n; j++) {
            sum += arr[j];
            best = max(sum, best);
        }
    }
    return best;
}

// O(n)
int max_subarray_sum_3 (int arr[], int n) {
    int best = 0, sum = 0;
    for (int k = 0; k < n; k++) {
        sum = max(arr[k], sum + arr[k]);
        best = max(best, sum);
    }
    return best;
}

int main() {
    int arr[] = {-5, -50, 12, -34, 100, 6, -40};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Algo 1 Max Subarray Sum is %d\n", max_subarray_sum_1(arr, n));
    printf("Algo 2 Max Subarray Sum is %d\n", max_subarray_sum_2(arr, n));
    printf("Algo 3 Max Subarray Sum is %d\n", max_subarray_sum_3(arr, n));
    return 0;
}
