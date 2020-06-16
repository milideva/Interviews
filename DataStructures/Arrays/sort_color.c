/* 
We are given an array of 0s and 1s in random order. Segregate 0s on left side
and 1s on right side of the array. Traverse array only once.

Segregate 0s and 1s in an array
*/

#include <stdio.h> 
#include <stdbool.h>
#include <string.h>

typedef enum color_ {
    black,
    white,
} color_t;

struct Block {
    enum color_ color;  // black or white
};

void sort_color (struct Block arr[], unsigned size) {
  
  int i = 0;
  int count = 0;
  
  while (i < size) {
    if (arr[i].color == white) {
      count++;
    }
    i++;
  }
  memset(arr, 0, size * sizeof arr[0]);
    
  i = 0;
  while (i < count) {
    arr[i].color = white;
    i++;
  }
}

static void swap (struct Block arr[], int i, int j) {

    color_t temp_color =  arr[i].color;
    arr[i].color = arr[j].color;
    arr[j].color = temp_color;
}

void sort_color_2 (struct Block arr[], unsigned size) {
    int left, right;
    left = 0;
    right = size-1; 
    color_t first = arr[0].color;

    while (left < right) { 
        if (arr[left].color != first) { 
            swap(arr, left, right); 
            right--;
            continue;
        } 
        left++;
    }
}

void print_arr (struct Block arr[], unsigned size) {
    for (int i = 0; i< size; i++) {
        printf("%d ", arr[i].color);
    }
    printf("\n");
}


int main(void) { 
    struct Block arr[10] = { 1, 0, 1, 1, 0, 0, 1, 1, 0, 0 }; 
    size_t size = sizeof arr/sizeof arr[0];

    print_arr(arr, size);
    sort_color_2(arr, size);
    print_arr(arr, size);

    return 0; 
}
