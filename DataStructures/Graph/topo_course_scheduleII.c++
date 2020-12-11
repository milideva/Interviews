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

*/

#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

class Solution {

    bool detectCycleRecur (int n, unordered_map <int, int> & color ) {
        if (color[n] == 1) return true;
        if (color[n] == 2 ) return false;
        
        color[n] = 1; // mark visited
        for (int i : adj[n]) {
            if (detectCycleRecur(i, color))
                return true;
        }
        
        color[n] = 2; // mark processed when done
        return false;
    }
    
    bool detectCycle (void) {
        int n = adj.size();
        unordered_map <int, int> color; // processed nodes are marked with a color
        for (int i = 0; i < n; i++) { // go through all adj edges
            if (color[i] == 0) {
                if (detectCycleRecur(i, color)) 
                    return true;
            }
        }
        return false;
    }
    void dfs (int course) {
        visited[course] = true;
        auto courseDep = adj[course];
        for (auto prereq : courseDep) {
            if (visited[prereq] == false) {
                dfs(prereq);
            }
        }
        result.push_back(course);
    }
            
    unordered_map <int, vector<int>> adj; // class Dependencies ai <--> {bi, ci, di}
    vector <bool> visited;
    vector <int> result;
    bool cycle;
    
public:

  // Using InDegree approach 
  vector<int> findOrder (int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDegree(numCourses, 0); // track the incoming edges  - array indexed by course#

    // Build adj graph and build inDegree counter
    for (int i = 0; i < prerequisites.size(); i++){
      int dst = prerequisites[i][1], src = prerequisites[i][0];  // src --> dst (dst is pre-requisite for src)
      adj[dst].push_back(src);   // src <------ dst (dst can be taken without issue, src can not be)
      inDegree[src]++; // incoming dependencies on src node    [src]++
    }

    queue<int> zeroDegree; // starting queue - with all 0 degree nodes
    vector<int> topoOrder; // topological sorted result o/p
    // Push 0 incoming nodes onto queue 
    for (int i = 0; i < inDegree.size(); i++){
      if (inDegree[i] == 0){
        zeroDegree.push(i); // no dependencies in zeroDegree 
        topoOrder.push_back(i); // results
      }
    }
    // Start with all 0 dependencis courses and 
    while (!zeroDegree.empty()){
      int node = zeroDegree.front();
      zeroDegree.pop();
      for (int i = 0; i < adj[node].size(); i++){
        int dst = adj[node][i];
        inDegree[dst]--;
        if (inDegree[dst] == 0){
          zeroDegree.push(dst);
          topoOrder.push_back(dst);
        }
      }
      // If no zero degree nodes exist, then it's a cycle
    }

    if (topoOrder.size() != numCourses){
      return vector<int>();
    }
    return topoOrder;
  }

/*

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Init
        visited.assign(numCourses, false);
        cycle = false;
        
        // no dependencies, any order of courses ...
        if (prerequisites.size() == 0) {
            while (numCourses) {
                result.push_back(numCourses-1);
                numCourses--;

            }
            return result;
        }
        // create graph - adj list of edges
        for (auto dep : prerequisites) {
            adj[dep[0]].push_back(dep[1]);
        }
        
        // Check for cycles 
        if (detectCycle() == true) 
          return {};
                
        // run through all the nodes, mistake running only through adj
        for (int i = 0; i < numCourses; i++) { 
            if (visited[i] == false) {
                dfs(i);
            }
        }
        return result;
    }
*/
};


int main () {

  class Solution sol;
  vector <vector <int>> v {{5,8},{3,5},{1,9},{4,5},{0,2},{7,8},{4,9}};

  vector<int> res = sol.findOrder(10, v);
  cout << "Topo sort on v1: ";
  for (auto i : res) {
    cout << i << " " ;
  }
  cout << endl;

  // cycle exists 
  vector <vector <int>> v2 { {2,5},{5,6},{6,7},{7,5} };
  vector<int> res2 = sol.findOrder(4, v2);

  cout << "Topo sort on v2 : ";
  for (auto i : res2) {
    cout << i << " " ;
  }

  cout << endl;
}
