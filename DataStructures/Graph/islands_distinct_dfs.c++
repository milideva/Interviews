
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <unordered_map> 

using namespace std;

/*
694. Number of Distinct Islands

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
(representing land) connected 4-directionally (horizontal or vertical.) You may
assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as
another if and only if one island can be translated (and not rotated or
reflected) to equal the other.

Example 1:
11000
11000
00011
00011

Given the above grid map, return 1.

Example 2:
11011
10000
00001
11011

Given the above grid map, return 3.

Notice that:
11
1
and
 1
11
are considered different island shapes, because we do not consider reflection / rotation.
Note: The length of each dimension in the given grid does not exceed 50.

*/

void dfs (vector<vector<int>>& grid, int i, int j, string& route) {
  grid[i][j] = 0;
  
  if (i-1 >= 0 && grid[i-1][j]) {
    route.push_back('u');
    dfs(grid, i-1, j, route);
  } else {
    route.push_back('n');
  }
  
  if (i+1 < grid.size() && grid[i+1][j]) {
    route.push_back('d');
    dfs(grid, i+1, j, route);
  } else {
    route.push_back('n');
  }
  
  if (j-1 >= 0 && grid[i][j-1]) {
    route.push_back('l');
    dfs(grid, i, j-1, route);
  } else {
    route.push_back('n');
  }
  
  if (j+1 < grid[0].size() && grid[i][j+1]) {
    route.push_back('r');
    dfs(grid, i, j+1, route);
  } else {
    route.push_back('n');
  }
}

void print_routes (unordered_map <string, int> routes) {
  for (auto [r, c]: routes) {
    cout << "route: " << r << " count:" << c << endl;
  }
}

int numDistinctIslands (vector<vector<int>>& grid) {
  if (grid.size() == 0 || grid[0].size() == 0) return 0;
  
  unordered_map <string, int> routes;
  
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j]) {
        string route = "";
        dfs(grid, i, j, route);
        routes[route]++;
      }
    }
    
  }
  print_routes(routes);
  return routes.size();
}

void test (vector<vector<int>> &grid) {

  int count = numDistinctIslands(grid);
  cout << "Num islands " << count << endl;
}

int main () {

  vector<vector<int>> grid = {{1, 1, 0, 0, 0},
                             {1, 1, 0, 0, 0},
                             {0, 0, 0, 1, 1},
                             {0, 0, 0, 1, 1}};
  test(grid);

  grid = { { 1, 1, 1, 1, 0}, 
            { 1, 1, 0, 1, 0}, 
            { 1, 1, 0, 0, 0},
            { 0, 0, 0, 0, 0},
  };
  test(grid);

  grid = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  };
  test(grid); // Expected: 1

  grid = {
    {1, 1, 0, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 0, 0, 1}
  };
  test(grid); // Expected: 2

  return 0;
}
