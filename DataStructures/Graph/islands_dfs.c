#include <stdio.h>
#include <stdbool.h>

/*
    Given a boolean 2D matrix, find the number of islands. A group of connected 1s
    forms an island. For example, the below matrix contains 5 islands
*/

#define ROWS 5
#define COLS 5


static bool check_valid (int i, int j) {
        return i >= 0 && i < ROWS && j >= 0 && j < COLS;
}

void dfs (int arr[][COLS], int i, int j, bool visited[][COLS]) {

    // 8 neighbors
    static int rowAdj[] = { -1, -1, -1, 0, 0, +1, +1, +1 };
    static int colAdj[] = { -1, 0, +1, -1, +1, -1, 0, +1 };

    visited[i][j] = true;

    for (int k = 0; k < 8; k++) {
        int iAdj = i + rowAdj[k];
        int jAdj = j + colAdj[k];

        bool is_valid = check_valid(iAdj, jAdj);
        if (is_valid && arr[iAdj] [jAdj] && !visited[iAdj] [jAdj]) {
            dfs(arr, iAdj, jAdj, visited);
       } 
    }
}

int count_islands (int arr[] [COLS]) {
    bool visited[ROWS][COLS] = {};
    int count = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (visited[i][j] == false && arr[i][j]) {
                dfs(arr, i, j, visited);
                count++;
            }
        }
    }
    return count;
}

int main () { 
    int M[][COLS] = { { 1, 1, 0, 0, 0 }, 
                     { 0, 1, 0, 0, 1 }, 
                     { 1, 0, 0, 1, 1 }, 
                     { 1, 0, 0, 0, 0 }, 
                     { 1, 0, 1, 0, 1 } }; 
  
    printf("Number of islands is: %d\n", count_islands(M)); 
  
    return 0; 
} 
