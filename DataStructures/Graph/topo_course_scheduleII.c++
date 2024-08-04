/*

207. Course Schedule

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
    unordered_map <int, vector<int>> prereqMap; // prereqMap[a] = b, c, d etc
    unordered_map <int, int> numPrereqs; // numPrereqs[a] = 3; a has 3 pre-req.s

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        // This init is necessary for the courses that have no pre-req.s
        for (int i = 0; i < numCourses; ++i) {
            numPrereqs[i] = 0;
        }
        
        vector <int> courses;
        for (auto vec: prerequisites) {
            auto a = vec[0]; // a depends on b
            auto b = vec[1];
            prereqMap[b].push_back(a);// course 'a' depends on b, b must come before a
            numPrereqs[a]++; // how many does course 'a' depend on?
        }

        queue <int> q;
        for (auto [course, numPrereqs]: numPrereqs) {
            if (numPrereqs == 0) {
                q.push(course);
            }
        }
        while (!q.empty()) {
            int course = q.front(); q.pop();
            courses.push_back(course); // take this class that does not depend on any other prereq
            for (auto dependent : prereqMap[course]) {
                numPrereqs[dependent]--;
                if (numPrereqs[dependent] == 0)
                    q.push(dependent);
            }
        }
        if (courses.size() == numCourses) {
            return true;
        }
        return false;
    } 
};

void testCanFinish() {
    Solution solution;

    vector<vector<int>> v1{{5, 8}, {3, 5}, {1, 9}, {4, 5}, {0, 2}, {7, 8}, {4, 9}};
    vector<vector<int>> v2{{1, 2}, {2, 3}, {3, 1}, {1, 0}};

    int numCourses1 = 10; // Number of courses for v1
    int numCourses2 = 4;  // Number of courses for v2

    // Test case 1
    bool result1 = solution.canFinish(numCourses1, v1);
    cout << "Test case 1: " << (result1 ? "True" : "False") << endl; // Expected output: True

    // Test case 2
    bool result2 = solution.canFinish(numCourses2, v2);
    cout << "Test case 2: " << (result2 ? "True" : "False") << endl; // Expected output: False
}

int main() {
    testCanFinish();
    return 0;
}

