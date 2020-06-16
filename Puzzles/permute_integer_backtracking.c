
#include <stdio.h>
#include <stdbool.h>

int array2num (int arr[], int size) {
    if (!size) 
        return 0;
    
    int num = 0;
    int index = 0;
    
    while (size) {
        num = num * 10 + arr[size-1];
        size--;
    }
    //printf("%s: num:%d\n", __FUNCTION__, num);
    return num;
}

bool num2array (int num, int **array, int *size) {
    int *arr;

    if (!size) 
        return false;
	
    int count = 0;
    int temp_num = num;

    while (num) {
        num = num/10;
        count++;
    }
    
    if (temp_num == 0) count = 1;
    
    num  = temp_num;

    arr =  malloc(count * sizeof(int));
    if (!arr)
        return false;

    int index = count;
    if (num == 0) {
        arr[0] = 0; *size = 1; 
        *array = arr;
        return true;
    }
    while (num) {
        arr[count-index] = num %10;
        num = num / 10;
        index--;
    }
    *size = count;
    *array = arr;
    return true;
}

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int count;

void permute (int arr[], int start, int end) {

    if (start == end) {

        int num = array2num(arr, end);
        printf("%s: num%d: %d\n", __FUNCTION__, ++count, num);
        return;
    }
    
    int i;
    
    for (i = start; i < end; i++) {
        /* Swap ith element in the loop with start element */
        swap(arr + start, arr + i);
        /* Pemute next element (start+1) */
        permute(arr, start+1, end);
        swap(arr + i, arr + start);
    }
}

void call_permute (int p_num) {
    int *arr = NULL;
    int size = 0;

    count = 0;
    if (!num2array(p_num, &arr, &size)) {
        printf("num2array failed\n");
        return;
    }
    printf("\n\nnum:%d size:%d array:%p\n", p_num, size, (void *) arr);
    permute(arr, 0, size);

    free(arr);
}

int main () {

    call_permute(123);
    
    call_permute(1234);

    call_permute(43);

    return 0;
}
