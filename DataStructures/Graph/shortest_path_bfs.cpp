#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

// g++ -std=c++14 shortest_path_bfs.cpp

#define ROWS 10
#define COLS 10

typedef struct node_ {
    int i, j;
    unsigned int dist;
} node_t;

static bool check_valid (int i, int j, int arr[][COLS], bool visited[][COLS]) {
    return i >= 0 && i < ROWS && j >= 0 && j < COLS && arr[i][j] && !visited[i][j];
}


unsigned int BFS (int arr[] [COLS], int isrc, int jsrc, int idst, int jdst) {

    bool visited[ROWS] [COLS] = {};

    queue <node_t> q;

    visited[isrc][jsrc] = true;

    q.push({isrc, jsrc, 0});

    while (!q.empty()) {
        node_t curr = q.front(); q.pop();
        // Found it, terminating condition
        if (curr.i == idst && curr.j == jdst) {
            return curr.dist;
        }

        // Check each neighbor
        for (int k = 0; k < 4; k++) {
            static int rowAdj[] = { -1, 0, 0, +1 };
            static int colAdj[] = { 0, -1, +1, 0 };
            int iAdj = curr.i + rowAdj[k];
            int jAdj = curr.j + colAdj[k];
            bool is_valid = check_valid(iAdj, jAdj, arr, visited);

            if (is_valid) {
                visited[iAdj][jAdj] = true;
                q.push( {iAdj, jAdj, curr.dist + 1} );
            }
        }
    }

    return 0;
}


int main() {
	// input maze
	int mat[ROWS][COLS] =
	{
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	};

	// Find shortest path from source (0, 0) to
	// destination (7, 5)
	unsigned dist = BFS(mat, 7, 3, 7, 5);
    cout << "Distance : " << dist << endl;

	return 0;
}

