/*
    79. Word Search
    Given an m x n grid of characters board and a string word, return true if word exists in the grid.

    The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. 
    The same letter cell may not be used more than once.

    Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
    Output: true

    Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
    Output: true

    Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
    Output: false
    
    Input: board = [["C","A","A"],["A","A","A"],["B","C","D"]], word ="AAB"
    Output: true

    Constraints:

    m == board.length
    n = board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board and word consists of only lowercase and uppercase English letters.

*/

/*
    Time: O(m * n * 4^|word|) => 4 recursive calls inside dfs
    Space: O(4^|word|) => function call stack for 4 recursive calls

*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int r;
    int c;
    bool isSafe (int i, int j) {
        if (i < 0 or j < 0 or i >= r or j >= c )
            return false;
        return true;
    }
    int x[4] = { 0, 0, +1, -1};
    int y[4] = { +1, -1, 0, 0};

    bool dfs (vector<vector<char>>& board, int i, int j,
            vector<vector<bool>>& visited, string& word, int wi) {
        
        if (wi == word.size() - 1)
            return true;
        if (!isSafe(i, j)) 
            return false;
        visited[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int ix = i + x[k];
            int jy = j + y[k];
            if (word[wi+1] != board[ix][jy] or visited[ix][jy])
                continue;

            // Typical mistake#1, return dfs unconditionally
            // should return only if word is found
            // otherwise continue the loop to try neighbors
            if (dfs(board, ix, jy, visited, word, wi+1)) 
                return true;
        }
        // Typical mistake#2, must backtrack here
        // The word was not found, mark it unvisited
        visited[i][j] = false;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty())
            return false;
        
        int rows = board.size();
        int cols = board[0].size();
        r = rows; 
        c = cols;
        vector <vector <bool>> visited(r, vector<bool> (c, false));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (word[0] != board[i][j] or visited[i][j])
                    continue;
                bool found = dfs(board, i, j, visited, word, 0);
                if (found) {
                    return true;
                }
            }
        }
        return false;
    }
};

void printBoard (vector <vector <char>> &board) {
    cout << endl << "Board: " << endl;
    for (auto v : board) {
        for (auto ch : v) {
            cout << ch << " ";
        }
        cout << endl;
    }
}
bool test (vector <vector <char>> &board, string word) {
    Solution sol;
    printBoard(board);
    cout << "word: " << word << endl;
    return sol.exist(board, word);
}

int main (void) {

    vector <vector <char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    string word = "ABCCED";
    bool output = test(board, word);
    cout << "found:" << output << endl;
    
    word = "SEE";
    output = test(board, word);
    cout << "found:" << output << endl;
    
    word = "ABCB";
    output = test(board, word);
    cout << "found:" << output << endl;
    
    board = {{'C','A','A'},{'A','A','A'},{'B','C','D'}};
    word = "AAB";
    output = test(board, word);
    cout << "found:" << output << endl;
    
    
    return 0;
}