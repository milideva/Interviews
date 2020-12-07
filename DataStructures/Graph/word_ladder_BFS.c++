
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#include <unordered_set>
#include <vector>

using namespace std;


/*

Given two words (beginWord and endWord), and a dictionary's word list, find the
length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time.
    Each transformed word must exist in the word list.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.
    You may assume no duplicates in the word list.
    You may assume beginWord and endWord are non-empty and are not the same.

Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

*/


int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
  
  int begL = beginWord.size();
  int endL = endWord.size();
  if (begL != endL) return 0;
  
  unordered_set <string> dict;
  
  for (auto s : wordList) {
    dict.insert(s);
  }
  if (dict.find(endWord) == dict.end()) return false;
  
  int len = begL;
  int level = 0;
  int changes = 0;
  
  queue <string> q;
  q.push(beginWord);
  
  while (!q.empty()) {
    level++;
    
    int szQ = q.size();
    while (szQ--) {
      string word = q.front();
      q.pop();
      for (int i = 0; i < len; i++) {
        // brute force, try all chars
        string temp = word;
        
        for (char ch = 'a'; ch <= 'z'; ch++) {    
          // skip the same char
          temp[i] = ch;
          if (temp == word) continue;
          //cout << " :" << ch << " " << word << " " << changes ;
          
          if (temp == endWord) {
            return level+1;
          }
          if (dict.find(temp) == dict.end()) {
            continue;
          }
          changes++;
          
          dict.erase(temp);
          q.push(temp);
        }
      }
      
    }
  }
  
  return 0;
}


int main () {

  vector <string> dict = { "hot","dot","dog","lot","log","cog" };

  int ll = ladderLength("hit", "cog", dict);

  cout << "Word ladder shortest path lenth : " << ll << endl;
  return 0;
}
