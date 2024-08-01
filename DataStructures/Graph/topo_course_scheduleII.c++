/*

There are a total of n courses you have to take labelled from 0 to n - 1.

Some courses may have prerequisites, for example, if prerequisites[i] = [ai, bi]
this means you must take the course bi before the course ai.

Given the total number of courses numCourses and a list of the prerequisite
pairs, return the ordering of courses you should take to finish all courses.

If there are many valid answers, return any of them. If it is impossible to
finish all courses, return an empty array.



Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]

Explanation: There are a total of 2 courses to take. To take course 1 you should
have finished course 0. So the correct course order is [0,1].

Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]

Explanation: There are a total of 4 courses to take. To take course 3 you should
have finished both courses 1 and 2. Both courses 1 and 2 should be taken after
you finished course 0. So one correct course order is [0,1,2,3]. Another correct
ordering is [0,2,1,3].

Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.

*/

#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
  vector<int> result;

public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {

    vector <int> indegrees(numCourses, 0);
    vector <vector <int>> preCourses(numCourses, vector<int>());

    for (auto pre: prerequisites) {
      auto u = pre[0];
      auto v = pre[1];
      // v must come before u
      preCourses[v].push_back(u);
      // someone before u
      indegrees[u]++;
    }

    // BFS
    // Push all vertices with 0 incoming edge
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
      if (indegrees[i] == 0)
        q.push(i);
    }

    while (!q.empty()) {
      // Remove the vertex with no incoming edges
      auto vertex = q.front();
      q.pop();
      // student has taken the pre-requisite
      result.push_back(vertex);
      // decrement indegree for each dependent class
      for (auto pre: preCourses[vertex]) {
        indegrees[pre]--;
        if (indegrees[pre] == 0)
          q.push(pre);
      }
    }

    if (result.size() == numCourses)
      return result;
    // If it is not equal, then a cycle exists!

    // cout << "Cycle: " << result.size() << endl;
    return {};
  }
};

int main () {

  class Solution sol;
  vector<vector<int>> v{{5, 8}, {3, 5}, {1, 9}, {4, 5}, {0, 2}, {7, 8}, {4, 9}};

  vector<int> res = sol.findOrder(10, v);
  cout << "Topo sort on v1: ";
  for (auto i: res) {
    cout << i << " ";
  }
  cout << "Done" << endl;

  // cycle exists
  vector<vector<int>> v2{{1, 2}, {2, 3}, {3, 1}, {1, 0}};
  vector<int> res2 = sol.findOrder(4, v2);

  cout << "Topo sort on v2 : ";
  for (auto i: res2) {
    cout << i << " ";
  }

  cout << endl;
}
