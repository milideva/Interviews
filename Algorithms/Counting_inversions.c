
/* 
https://www.youtube.com/watch?v=yP0asUjcrBA

Finding "similarity" between two rankings. 

Given a sequence of n numbers 1..n (assume all numbers are distinct). 
Define a measure that tells us how far this list is from being in order.  
The value should be 0 for a sorted list. 
should be higher as the list is more "out of order".  
Maximum inversions when sorted in reverse.
n * (n-1) / 2
for 6 elements array => 15 max inversions.

Define the number of inversion i, j form an inversion 
if a_i > a_j, that is, if the two elements a_i and a_j are "out of order".

Comparing two rankings is counting the number of  inversion in the sequence.

Example
2 4 1 3 5
1 2 3 4 5

The sequence 2, 4, 1, 3, 5 has three inversions (2,1), (4,2), (4,3).

1 4 2 3 5 --> after (2,1)
1 2 4 3 5 --> after (4,2)
1 2 3 4 5 --> after (4,3)

This is used by NetFlix or Amazon etc to compare rankings done by users.
Based on with whom your rankings match, they recommend products/movies.

Very neat application!

*/

/* O(n^2) solution */
int count_inversions (int array[], int size) {
    int i, j, inv;
    inv = 0;
    
    for (i = 0; i < size-1; i++) {
        for (j = i+1; j < size; j++) {
            if (array[i] < array[j])
                inv++;
        }
    }
    return inv;
}

/* Better way : divide and conquer nlogn like in mergesort */
int main (void) {
    int array[] = { 1, 20, 6, 4, 5 };
    int size = sizeof(array)/sizeof(array[0]);

    printf("count inversions: %d\n", 
           count_inversions(array, size));
    return 0;
}
