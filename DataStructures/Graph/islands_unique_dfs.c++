
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <unordered_map> 

using namespace std;

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
  
  return routes.size();
}

int main () {

  vector<vector<int>> myvect = { { 1, 1, 1, 1, 0}, 
                                 { 1, 1, 0, 1, 0}, 
                                 { 1, 1, 0, 0, 0},
                                 { 0, 0, 0, 0, 0},
  };

  int count = numDistinctIslands(myvect);
  cout << "Num islands " << count << endl;
  return 0;
}
