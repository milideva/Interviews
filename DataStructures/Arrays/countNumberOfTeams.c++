/*

    1395. Count Number of Teams

There are n soldiers standing in a line. Each soldier is assigned a unique rating value.

You have to form a team of 3 soldiers amongst them under the following rules:

Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).

Example 1:
Input: rating = [2,5,3,4,1]
Output: 3
Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1). 

Example 2:
Input: rating = [2,1,3]
Output: 0
Explanation: We can't form any team given the conditions.

Example 3:
Input: rating = [1,2,3,4]
Output: 4

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int numTeams (vector <int>& rating) {
        int sz = rating.size();
        if (sz < 3) return 0;
        int leftLess, leftGreater, rightLess, rightGreater;
        int sum = 0;
        for (int i = 1; i < sz - 1; i++) {
            leftLess = leftGreater = rightLess = rightGreater = 0;
            // Left loop
            for (int j = 0; j < i; j++) {
                if (rating[j] < rating[i])
                    leftLess++;
                if (rating[j] > rating[i])
                    leftGreater++;
            }
            // Right loop
            for (int j = i+1; j < sz; j++) {
                if (rating[j] > rating[i])
                    rightGreater++;
                if (rating[j] < rating[i])
                    rightLess++;
            }

            sum += (leftLess * rightGreater) + (leftGreater * rightLess);
        }
        return sum;
    }
};

int main(void) {

    vector <int> rating {2,5,3,4,1};
    class Solution sol;
    auto sum = sol.numTeams(rating);
    cout << "Number of teams: " << sum << endl;

    vector <int> rating2 {1, 2, 3, 4};
    sum = sol.numTeams(rating2);
    cout << "Number of teams: " << sum << endl;
    return 0;
}