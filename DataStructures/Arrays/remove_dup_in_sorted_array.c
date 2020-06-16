/* Array must be sorted */
int remove_duplicates (int array[], int size) {
    int uniq = 0;
    int i;

    for (i=1; i < size; i++) {
        if (array[i] != array[uniq]) {
            uniq++;
            array[uniq] = array[i];
        }
    }
    return uniq+1; // new array size.
}
        
void print_array (int array[], int size) {
    int i;
    printf("\narray[%d] : ", size);
    for (i=0; i<size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
    
int main () {
    /* Array must be sorted */

    int array[] = { 0, 0, 0, 2, 2, 55, 56, 56, 200, 200, 201,201};
    int count = remove_duplicates(array, sizeof array/sizeof array[0]);
    print_array(array, count);

    return 0;
}
