
/*
    36. Valid Sudoku

Determine if a 9 x 9 Sudoku board is valid. 
Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

*/
#include <iostream>       // std::cout
#include <vector>

using namespace std;

class Solution {
    
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9][9] = {{0}};
        int cols[9][9] = {{0}};
        int squares[9][9] = {{0}};

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                int ch = board[i][j];
                if (ch == '.') 
                    continue;
                ch = board[i][j] - '0' - 1; // There is no 0 in Sudoku
                if (rows[i][ch]) 
                    return false;
                if (cols[j][ch])
                    return false;
                int k = ( i / 3 ) * 3 + j / 3;
                if (squares[k][ch])
                    return false;
                rows[i][ch] = cols[j][ch] = squares[k][ch] = 1;
                /*
                    k = i / 3 * 3 + j / 3
                    to visualize k > here

                    0  0  0 | 1  1  1 | 2  2  2
                    0  0  0 | 1  1  1 | 2  2  2
                    0  0  0 | 1  1  1 | 2  2  2
                    --------+---------+---------
                    3  3  3 | 4  4  4 | 5  5  5
                    3  3  3 | 4  4  4 | 5  5  5
                    3  3  3 | 4  4  4 | 5  5  5
                    --------+----------+--------
                    6  6  6 | 7  7  7 | 8  8  8
                    6  6  6 | 7  7  7 | 8  8  8
                    6  6  6 | 7  7  7 | 8  8  8

                */
            }
        }
        return true;
    }
};


void testSudoku (vector<vector<char>> &board) {
    Solution sol;
    bool isValid = sol.isValidSudoku(board);
    cout << "isValid: " << isValid << endl;
}

int main () {
    vector<vector<char>> board = {
    {'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}};
    
    testSudoku(board);
    
    vector<vector<char>> board2 = 
    {{'8','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'8','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}};
    
    testSudoku(board2);
    
    return 0;   
}