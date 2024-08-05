/*

212. Word Search II
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 
 Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []

*/

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    string word;

    TrieNode() : word("") {}
};

class Solution {
private:
    vector<vector<char>> _board;
    vector<string> _result;

public:
    vector<string> findWords(vector<vector<char>>& board,
                             vector<string>& words) {
        // Step 1). Construct the Trie
        TrieNode* root = new TrieNode();
        for (string& word : words) {
            TrieNode* node = root;
            for (char letter : word) {
                if (node->children.find(letter) != node->children.end()) {
                    node = node->children[letter];
                } else {
                    TrieNode* newNode = new TrieNode();
                    node->children[letter] = newNode;
                    node = newNode;
                }
            }
            node->word = word;  // store words in Trie
        }

        this->_board = board;
        // Step 2). Backtracking starting for each cell in the board
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[row].size(); ++col) {
                if (root->children.find(board[row][col]) !=
                    root->children.end()) {
                    backtracking(row, col, root);
                }
            }
        }

        return this->_result;
    }

private:
    void backtracking(int row, int col, TrieNode* parent) {
        char letter = this->_board[row][col];
        TrieNode* currNode = parent->children[letter];

        // check if there is any match
        if (currNode->word != "") {
            this->_result.push_back(currNode->word);
            currNode->word = "";  // prevent duplicate entries
        }

        // mark the current letter before the EXPLORATION
        this->_board[row][col] = '#';

        // explore neighbor cells in around-clock directions: up, right, down,
        // left
        int rowOffset[] = {-1, 0, 1, 0};
        int colOffset[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; ++i) {
            int newRow = row + rowOffset[i];
            int newCol = col + colOffset[i];
            if (newRow < 0 || newRow >= this->_board.size() || newCol < 0 ||
                newCol >= this->_board[0].size()) {
                continue;
            }
            if (currNode->children.find(this->_board[newRow][newCol]) !=
                currNode->children.end()) {
                backtracking(newRow, newCol, currNode);
            }
        }

        // End of EXPLORATION, restore the original letter in the board.
        this->_board[row][col] = letter;

        // Optimization: incrementally remove the leaf nodes
        if (currNode->children.empty()) {
            parent->children.erase(letter);
        }
    }
};

void runTest(vector<vector<char>> board, vector<string> words, vector<string> expected) {
    Solution solution;
    vector<string> result = solution.findWords(board, words);
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());

    cout << "Result: ";
    for (const string& word : result) {
        cout << word << " ";
    }
    cout << endl;

    cout << "Expected: ";
    for (const string& word : expected) {
        cout << word << " ";
    }
    cout << endl;

    if (result == expected) {
        cout << "Test Passed" << endl;
    } else {
        cout << "Test Failed" << endl;
    }
}

int main() {
    vector<vector<char>> board1 = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words1 = {"oath", "pea", "eat", "rain"};
    vector<string> expected1 = {"eat", "oath"};
    runTest(board1, words1, expected1);

    vector<vector<char>> board2 = {
        {'a','b'},
        {'c','d'}
    };
    vector<string> words2 = {"abcb"};
    vector<string> expected2 = {};
    runTest(board2, words2, expected2);

    return 0;
}