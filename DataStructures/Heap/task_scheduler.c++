#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

/*

Given a characters array tasks, representing the tasks a CPU needs to do, where
each letter represents a different task. Tasks could be done in any order. Each
task is done in one unit of time. For each unit of time, the CPU could complete
either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period
between two same tasks (the same letter in the array), that is that there must
be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all
the given tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.

Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.

Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A

*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map <char, int> counts;
        for (auto t: tasks) {
            counts[t]++;
        }
        
        priority_queue <int> pq;
        for (auto chcntPair: counts) {
            pq.push(chcntPair.second);
        }
        
        int result = 0;
        while (!pq.empty()) {
            int time = 0;
            vector <int> tmp;
            for (int i = 0; i < n+1; i++) { // n+1 because, current task 1 slot, + we've to wait for n slots cooling period
              tmp.push_back(pq.top() - 1); // consume 1 , task, save it in tmp with count 1 less
              pq.pop();
              time++;
              if (pq.empty())
                break;
            }
            for (auto t : tmp) {
                if (t) pq.push(t);
            }
            result += pq.empty() ? time : n+1;
        }
        
        return result;        
    }
};


/* 
Easier to do mathematically : Java version 

class Solution {
    public int leastInterval(char[] tasks, int n) {
        // frequencies of the tasks
        int[] frequencies = new int[26];
        for (int t : tasks) {
            frequencies[t - 'A']++;
        }

        // max frequency
        int f_max = 0;
        for (int f : frequencies) {
            f_max = Math.max(f_max, f);
        }
        
        // count the most frequent tasks
        int n_max = 0;
        for (int f : frequencies) {
            if (f == f_max) n_max++;
        }
        // fmax-1 because last round, no cooling period, so for last round it is only n_max
        return Math.max(tasks.length, (f_max - 1) * (n + 1) + n_max);
    }
}

int main () {
  class Solution sol;
  vector <char> tasks = {'A','A','A','B','B','B'};
  int result, n = 0;

  result = sol.leastInterval(tasks, n);
  cout << "task scheduler least #cpu units: " << result << " for n:" << n << endl;
  
  n = 2;
  result = sol.leastInterval(tasks, n);
  cout << "task scheduler least #cpu units: " << result << " for n:" << n << endl;

  return 0;
}

