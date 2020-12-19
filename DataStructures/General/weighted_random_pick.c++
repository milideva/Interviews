/*

You are given an array of positive integers w where w[i] describes the weight of
ith index (0-indexed).

We need to call the function pickIndex() which randomly returns an integer in
the range [0, w.length - 1]. pickIndex() should return the integer proportional
to its weight in the w array. For example, for w = [1, 3], the probability of
picking the index 0 is 1 / (1 + 3) = 0.25 (i.e 25%) while the probability of
picking the index 1 is 3 / (1 + 3) = 0.75 (i.e 75%).

More formally, the probability of picking index i is w[i] / sum(w).

 

Example 1:

Input
["Solution","pickIndex"]
[[[1]],[]]
Output
[null,0]

Explanation
Solution solution = new Solution([1]);

solution.pickIndex(); // return 0. Since there is only one single element on the
array the only option is to return the first element.

Example 2:

Input
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output
[null,1,1,1,1,0]

Explanation
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // return 1. It's returning the second element (index = 1) that has probability of 3/4.
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 0. It's returning the first element (index = 0) that has probability of 1/4.

Since this is a randomization problem, multiple answers are allowed so the following outputs can be considered correct :
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
and so on.

Constraints:

    1 <= w.length <= 10000
    1 <= w[i] <= 10^5
    pickIndex will be called at most 10000 times.

*/

#include <vector>
#include <iostream>
using namespace std;

/*

Given a list of positive values, we are asked to randomly pick up a value based
on the weight of each value. To put it simple, the task is to do sampling with
weight.

Let us look at a simple example. Given an input list of values [1, 9], when we
pick up a number out of it, the chance is that 9 times out of 10 we should pick
the number 9 as the answer.

In other words, the probability that a number got picked is proportional to the
value of the number, with regards to the total sum of all numbers.

To understand the problem better, let us imagine that there is a line in the
space, we then project each number into the line according to its value, i.e. a
large number would occupy a broader range on the line compared to a small
number. For example, the range for the number 9 should be exactly nine times as
the range for the number 1.

Now, let us throw a ball randomly onto the line, then it is safe to say there is
a good chance that the ball will fall into the range occupied by the number 9.
In fact, if we repeat this experiment for a large number of times, then
statistically speaking, 9 out of 10 times the ball will fall into the range for
the number 9.

That is the intuition behind this problem.

The offsets of the ranges are actually the prefix sums from a sequence of
numbers. For each number in a sequence, its corresponding prefix sum, also known
as cumulative sum, is the sum of all previous numbers in the sequence plus the
number itself.

As an observation from the definition of prefix sums, one can see that the list
of prefix sums would be strictly monotonically increasing, if all numbers are
positive.

To throw a ball on the line is to find an offset to place the ball. Let us call
this offset target.

Once we randomly generate the target offset, the task is now boiled down to
finding the range that this target falls into.

Let us rephrase the problem now, given a list of offsets (i.e. prefix sums) and
a target offset, our task is to fit the target offset into the list so that the
ascending order is maintained.

*/

class Solution {
  vector<int> sum;
public:
  Solution(vector<int>& w) {
    for (int i : w) {
      int n = sum.empty() ? i : i + sum.back();
      sum.push_back(n);
    }
  }
  
  int pickIndex() {
    int m = sum.back();
    int r = rand() % m;
    auto it = upper_bound(sum.begin(), sum.end(), r);
    return it - sum.begin();
  }
};

int main () {
  vector <int> v { 1, 3 }; 
  class Solution sol(v);
 
  int c, max = 12;
  c = 1;
  while (c <= max) {
    int res = sol.pickIndex();
    cout << "#" << c << " picked : " << res << endl;
    c++;
  }
  /* Out of 12 outcomes : index 0 got picked 3 times and index 1 got picked 9 times  */
/*
#1 picked : 1
#2 picked : 1
#3 picked : 1
#4 picked : 1
#5 picked : 1
#6 picked : 0
#7 picked : 0
#8 picked : 1
#9 picked : 1
#10 picked : 1
#11 picked : 0
#12 picked : 1
*/
  return 0;
}
