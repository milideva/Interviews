#include <stdlib.h>
#include <stdio.h>

/* Create 2-D dynamic array. 
   Requirement: one should be able to access it by arr[i][j]
*/
int **alloc_dynamic_2d_array(int row, int col) {
    int **arr;
    int i, j;
    arr = malloc(row * sizeof (*arr));
    for (i=0; i<row; i++)
        arr[i] = malloc(col * sizeof(**arr));
    return arr;
}

void free_dynamic_2d_array(int **arr, int row) {
    int i;
    for (i=0; i<row; i++)
        free(arr[i]);
    free(arr);
}

void use_array (int row, int col) {
    int **arr;
    arr = alloc_dynamic_2d_array(row, col);

    if (!arr) return;

    int i,j, count = 0;

    for (i=0; i<row; i++) {
        printf("\narr[%d][0..%d]: ", i, col);
        for (j=0; j<col; j++) {
            arr[i][j] = count++;
            printf("%d ", arr[i][j]);
        }
    }
    free_dynamic_2d_array(arr, row);
}

int main (void) {

    use_array(5, 10);
}
