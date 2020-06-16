#include <stdlib.h>

int array2num (int arr[], int size) {
    int i, num;
    num = 0;
    /* MSB in 0th array position */
    for (i=0; i<size; i++) {
        num = num * 10 + arr[i]; 
    }
    printf("%s: number is %d\n", __FUNCTION__, num);
    return num;
}

int *num2array (int num, int *size) {
    int i;
    if (!size) return NULL;

    if (!num) {
        *size = 1;
    } else {
        *size = 0;
        int n = num;
        while (n) {
            (*size)++;
            n /= 10;
        }
    }
    
    int *arr = malloc(sizeof(int) * *size);
    if (!arr) return NULL;
    
    for (i = *size-1; i>=0; i--) {
        arr[i] = num % 10;
        num /= 10;
    }
    printf("\n %s ", __FUNCTION__);
    for (i=0; i<*size; i++) {
        /* MSB in 0th position, LSB at size-1 position in array */
        printf("array[%d]: %d , ", i, arr[i]);
    }
    return arr;
}

int add_array (int *arr1, int sz1, int *arr2, int sz2, int **arr, int *sz) {
    int n1 = array2num(arr1, sz1);
    int n2 = array2num(arr2, sz2);
    *sz = 0;
    *arr = num2array(n1+n2, sz);
    return 0;
}

int main () {
    int sz1, sz2, sz3;
    int *array1;
    array1 = num2array(345, &sz1);

    int array2[] = { 1, 2, 3, 4, 5 };
    sz2 = sizeof array2/sizeof array2[0];

    array2num(array2, sz2);
    int *array3 = malloc(sizeof *array3);
    add_array(array1, sz1, array2, sz2, &array3, &sz3);

    return 0;
}
