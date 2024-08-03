#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
X-Sum
You are given an NxM chessboard where every cell has a non-negative integer value written on it. Place a bishop on the board such that the sum of all cells attacked by the bishop is maximal. Return the maximal value.
The bishop attacks in all directions diagonally, and there is no limit to the distance which the bishop can attack. Note that the cell on which the bishop is placed is also considered attacked.
Sample Input #1
N = 4, M = 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4

Sample Output #1
20
*/

// time complexity O(N∗M∗4∗min(N,M))

// Function to calculate the sum of all cells attacked by the bishop at position (x, y)
int calculateSum(const vector<vector<int>>& board, int x, int y, int N, int M) {
    int sum = 0;
    // Directions: top-left, top-right, bottom-left, bottom-right
    int dx[] = {-1, -1, 1, 1};
    int dy[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int nx = x, ny = y;
        while (nx >= 0 && nx < N && ny >= 0 && ny < M) {
            sum += board[nx][ny];
            nx += dx[i];
            ny += dy[i];
        }
    }

    // Subtracting the value at (x, y) three times since it is added four times in the loop
    return sum - 3 * board[x][y];
}

int getMaxBishopAttackSum(const vector<vector<int>>& board, int N, int M) {
    int maxSum = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int currentSum = calculateSum(board, i, j, N, M);
            maxSum = max(maxSum, currentSum);
        }
    }

    return maxSum;
}

void runTestCase(vector<vector<int>> board, int N, int M, int expected) {
    int result = getMaxBishopAttackSum(board, N, M);
    cout << "Result: " << result << ", Expected: " << expected << endl;
    cout << (result == expected ? "PASS" : "FAIL") << endl;
}

int main() {
    // Sample Input #1
    vector<vector<int>> board1 = {
        {1, 2, 2, 1},
        {2, 4, 2, 4},
        {2, 2, 3, 1},
        {2, 4, 2, 4}
    };
    runTestCase(board1, 4, 4, 20);

    // Sample Input #2
    vector<vector<int>> board2 = {
        {1},
        {0}
    };
    runTestCase(board2, 2, 1, 1);

    // Sample Input #3
    vector<vector<int>> board3 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    runTestCase(board3, 3, 3, 5);

    // Sample Input #4
    vector<vector<int>> board4 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    runTestCase(board4, 3, 3, 3);

    // Additional Test Case #1: Small board with same values
    vector<vector<int>> board5 = {
        {1, 1},
        {1, 1}
    };
    runTestCase(board5, 2, 2, 4);

    // Additional Test Case #2: Single cell board
    vector<vector<int>> board6 = {
        {5}
    };
    runTestCase(board6, 1, 1, 5);

    // Additional Test Case #3: Large board with random values
    vector<vector<int>> board7 = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    runTestCase(board7, 5, 5, 105);

    return 0;
}
