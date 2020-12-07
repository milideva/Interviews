
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

struct PairString {
  string first;
  string second;

   PairString(string first, string second) : first(first), second(second) {}
};

class Solution {

  unordered_map <string, int> str2idMap;
  unordered_map <int, string> id2strMap;
  vector <int> parent;
  vector <int> rank;

  int maxRank;
  int maxRankId;
  int totalId;

  void print (string s) {
    
    cout << s << endl << "ID ";
    for (int i = 0; i < totalId; i++)
      cout << "\t" << i;

    cout << endl << "Parent ";
    for (auto p : parent) 
      cout << "\t" << p;

    cout << endl << "Rank " ;
    for (auto r : rank) 
      cout << "\t" << r;
    cout << endl << endl;
  }

  int find (int i) {
    if (parent[i] == -1) return i;
    int p = find(parent[i]);
    int ap = p;
    while (-1 != parent[p]) {
      ap = p;
      p = find(parent[p]);
    }
    parent[i] = ap;
    //rank[p]++;
    return p;
  }

  void ds_union (int x, int y) {

    //print("ds_union: enter ");
    int xset = find(x);
    int yset = find(y);

    if (rank[xset] < rank[yset]) {
      parent[xset] = yset;
      rank[yset] += rank[xset];
      rank[xset] = 0;
      if (rank[yset] > maxRank) {
        maxRank = rank[yset] + 1; 
        maxRankId = yset;
      }
    } else {
      parent[yset] = xset;
      rank[xset] += rank[yset] + 1;
      rank[yset] = 0;
      if (rank[xset] > maxRank) {
        maxRank = rank[xset];
        maxRankId = xset;
      }
    }
    //print("ds_union: exit ");
  }

public:

   Solution() {
     maxRank = -1;
     maxRankId = -1;
     totalId = 0;
   }

   vector<string> largestItemAssociation(vector<PairString>& itemAssociation) {
     int counter = 0;
     for (auto pair: itemAssociation) {
       if (str2idMap.find(pair.first) == str2idMap.end()) {
         str2idMap[pair.first] = counter;
         id2strMap[counter] = pair.first;
         //cout << pair.first << ":" << counter << endl;
         counter++;
       }

       if (str2idMap.find(pair.second) == str2idMap.end()) {
         str2idMap[pair.second] = counter;
         id2strMap[counter] = pair.second;
         //cout << pair.second << ":" << counter << endl;
         counter++;
       }
     }
     totalId = counter;
     parent.resize(counter, -1);
     rank.resize(counter, 0);

     for (auto pair: itemAssociation) {
       int id1 = str2idMap[pair.first];
       int id2 = str2idMap[pair.second];
       int p1 = find(id1);
       int p2 = find(id2);
       // cout << pair.first << " : " << pair.second << endl;
       if (p1 != p2) {
         ds_union(p1, p2);
       }
     }
     
     vector <string> result;

     if (maxRank != -1) {
       for (int i = 0; i < parent.size(); i++) {
         if (find(i) == maxRankId) {
           result.push_back(id2strMap[i]);
         }
       }
     }
     
     return result;
   }

};

int main() {
   Solution sol;

   vector<PairString> itemAssociation = {PairString("item1","item2"), PairString("item2","item3"), 
        PairString("item4","item5"), PairString("item6","item7"),PairString("item5","item6"),
        PairString("item3","item7")};

   //vector<PairString> itemAssociation = {PairString("item1","item2"), PairString("item3","item4"), PairString("item4","item5")};
   //vector<PairString> itemAssociation = {PairString("item1","item2"), PairString("item3","item4"), PairString("item5", "item6")};
   //vector<PairString> itemAssociation = {PairString("item1","item2"), PairString("item2","item3"), PairString("item4", "item5"), PairString("item5","item6")};
   vector<string> itemAssoc = sol.largestItemAssociation(itemAssociation);
   cout << "The item association is : " << endl;
   for (auto& item : itemAssoc)
      cout << item << " ";
   cout << endl;
}
