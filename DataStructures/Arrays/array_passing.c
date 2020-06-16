#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 5


/* 
   If we want to leave out any dimensions, we can only leave out the first one
*/
static void func (int array[][COLS]) {
    int i, j;
    
    for (i=0; i<ROWS; i++) {
        for (j=0; j<COLS; j++) {
            array[i][j] = i*j;
        }
    }
}

/* 
   variable length array is a feature of C99.
   gcc -pedantic array_passing.c
   array_passing.c:19: warning: ISO C90 forbids variable-size array `array'
*/

static void func_vla (int rows, int cols, int array[rows][cols]) {
    int i, j;

    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            array[i][j] = i*j;
        }
    }
}

static void func_dynamic (int** array, int rows, int cols) {
    int i, j;
    
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            array[i][j] = i*j;
        }
    }
}

static void print_array (int** array, int rows, int cols) {
    int i, j;
    
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

/* allocate a 2-D array such that it can be used array[m][n] */
/* http://www.eskimo.com/~scs/cclass/int/sx9b.html 
 */
int ** allocate_array (int m, int n) {
    int **array;
    int nrows = m;
    int ncols = n;
    int i;
    
    array = malloc(nrows * sizeof(*array));
    if (!array) return NULL;
    
    for (i= 0; i < nrows; i++) {
        array[i] = calloc(1, ncols * sizeof(**array));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }
    
    return array;
}

void deallocate_array (int **array, int rows) {
    int i;
    for (i = 0; i < rows; i++) {
        free(array[i]); // Free the columns
    }
    free(array); // Free the rows
}

/*
The differences between the pointers are not so much ‘where they point’ as, how much they point-to.  
All three pointers certainly allow you to locate the 0 in matrix[0][0], and if you convert these pointers to ‘byte addresses’ and print them out with a %p directive in printf(), 
all three are quite likely to produce the same output (on a typical modern computer).  
But the int * pointer, p1, points only to a single int.  
p2, whose type is int (*)[2], points to two ints, 
p3 points to the entire matrix.
These differences affect the results of both pointer arithmetic and the unary * (indirection) operator.  Since p1 points to a single int, p1 + 1 moves forward by a single int.
*/    
void array_pointers (void) {
    int matrix [4][2] = { {0,1}, {2,3}, {4,5}, {6,7} };
    int (*p1) = &matrix[0][0];
    int (*p2)[2] = &matrix[0];
    int (*p3)[4][2] = &matrix;
    printf("p1:%p p2:%p p3:%p\n", p1, p2, p3);
}


int main() {
    int x[ROWS][COLS];
    int rows = ROWS;
    int cols = COLS;

    array_pointers();
    return 0;

    func(x);
    func_vla(rows, cols, x);

    int **array, i;
    /* allocate a dynamic size array */ 
    array = allocate_array(ROWS, COLS);
    /* Use it */
    func_dynamic(array, ROWS, COLS);
    
    /* deallocate the array */
    deallocate_array(array, ROWS);
    
    array = allocate_array(rows, cols);
    func_dynamic(array, rows, cols);
    print_array(array, rows, cols);

    return 0;
}
