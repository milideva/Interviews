#include <vector>
#include <iostream>
using namespace std;

/*
    37. Sudoku Solver
    Write a program to solve a Sudoku puzzle by filling the empty cells.

    A sudoku solution must satisfy all of the following rules:

    Each of the digits 1-9 must occur exactly once in each row.
    Each of the digits 1-9 must occur exactly once in each column.
    Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
    The '.' character indicates empty cells.

    Constraints:

    board.length == 9
    board[i].length == 9
    board[i][j] is a digit or '.'.
    It is guaranteed that the input board has only one solution.
    
*/

class Solution {
public:
    bool solveSudoku(vector<vector<char>> &board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    vector<char> values = getPossibleValues(board, i, j);
                    if (values.empty()) {
                        return false;
                    }
                    for (char value : values) {
                        board[i][j] = value;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[i][j] = '.';
                    }
                    return false;
                }
            }
        }
        return true;
    }

    vector<char> getPossibleValues(vector<vector<char>> &board, int row, int col) {
        vector<char> values;
        for (char c = '1'; c <= '9'; c++) {
            if (isValid(board, row, col, c)) {
                values.push_back(c);
            }
        }
        return values;
    }

    bool isValid (vector<vector<char>> &board, int row, int col, char value) {
        // check row
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == value) {
                return false;
            }
        }

        // check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == value) {
                return false;
            }
        }

        // check 3x3 box
        int r = row / 3 * 3;
        int c = col / 3 * 3;
        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                if (board[i][j] == value) {
                    return false;
                }
            }
        }

        return true;
    }
};

void printBoard(vector<vector<char>> &board)
{
    cout << "board: " << endl;
    for (auto vec : board)
    {
        for (auto v : vec)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(void)
{

    vector<vector<char>> board =
        {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
         {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
         {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
         {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
         {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
         {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
         {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
         {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
         {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    printBoard(board);
    Solution sol;
    sol.solveSudoku(board);
    printBoard(board);
    return 0;
}