
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#include <unordered_set>
#include <vector>

using namespace std;


/*

127. Word Ladder
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.

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
  
  queue <string> q;
  q.push(beginWord);
  
  while (!q.empty()) {
    level++;
    
    int szQ = q.size();
    while (szQ--) {
      string word = q.front();
      q.pop();
        
      // brute force, try all chars
      for (int i = 0; i < len; i++) {
        string temp = word;
        for (char ch = 'a'; ch <= 'z'; ch++) {    
          // skip the same char
          temp[i] = ch;
          if (temp == word) continue;
          //cout << " :" << ch << " " << word << " " << changes ;
          
          if (temp == endWord) {
            return level + 1;
          }
          if (dict.find(temp) == dict.end()) {
            continue;
          }
          // matched a transient word !!
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
