#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class Solution {
  typedef struct point_ {
    int x;
    int y;
  } point;
  point points[4];
  vector <double> distance;
  double getDistance(point p1, point p2) {
    int dx = abs(p1.x - p2.x);
    int dy = abs(p1.y - p2.y);
    return sqrt( dx * dx + dy * dy);
  }
public:
  bool isRectangle(vector<vector<int>> pointsVec) {
    if (pointsVec.size() != 4) return false;
    for (int i = 0; i < 4; i++) {
      vector <int> vec = pointsVec[i];
      points[i].x = vec[0];
      points[i].y = vec[1];
    }
    for (int i = 0; i < 3; i++) {
      for (int j = i+1; j < 4; j++) {
	double dist = getDistance(points[i], points[j]);
	distance.push_back(dist);
      }
    }
    sort(begin(distance), end(distance));
    if (distance[0] != distance[1]) return false;
    if (distance[2] != distance[3]) return false;
    if (distance[4] != distance[5]) return false;
    return true;
  }
};

int main () {
  vector <vector<int>> points;
  points.push_back({0,0});
  points.push_back({5,0});
  points.push_back({0,3});
  points.push_back({5,2});

  Solution sol;
  cout << "isRectangle: " << sol.isRectangle(points) << endl;
  return 0;
}
