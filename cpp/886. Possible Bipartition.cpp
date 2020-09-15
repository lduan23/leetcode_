/* 886. Possible Bipartition
https://leetcode.com/problems/possible-bipartition/

Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.
Each person may dislike some other people, and they should not go into the same group. 
Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.
Return true if and only if it is possible to split everyone into two groups in this way.

Example 1:

Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4], group2 [2,3]
Example 2:

Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Example 3:

Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false
 
Constraints:

1 <= N <= 2000
0 <= dislikes.length <= 10000
dislikes[i].length == 2
1 <= dislikes[i][j] <= N
dislikes[i][0] < dislikes[i][1]
There does not exist i != j for which dislikes[i] == dislikes[j].
*/

#include <vector>
#include <queue>
using namespace std;

class Solution_bfs {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        // bfs
        vector<vector<int>> adj (N + 1);
        vector<int> group (N + 1, -1);
        
        for (auto &v : dislikes) {
            adj[v[0]].push_back(v[1]);
            adj[v[1]].push_back(v[0]);
        }
        
        queue<int> q;
        int color {0};
        
        for (int i = 1; i <= N; i++) {
            if (group[i] == -1) {
                q.push(i);
                group[i] = color;
                
                while (!q.empty()) {

                    int size = q.size();

                    while (size-- > 0) {
                        int u = q.front();
                        q.pop();

                        for (int j = 0; j < adj[u].size(); j++) {
                            int v = adj[u][j];
                            if (group[v] == -1) {
                                group[v] = !color;
                                q.push(v);
                            } else if (group[v] == color)
                                return false;
                        }
                    }
                    color = !color;
                }
            }
        }
        return true;
    }
};


    // dfs
class Solution_dfs {
public:
    void dfs(vector<vector<int>> &adj, vector<int> &group, int color, int i) {
        if (group[i] != -1)
            return;
        group[i] = color;
        for (int j = 0; j < adj[i].size(); j++) {
            dfs(adj, group, !color, adj[i][j]);
        }
    }
    
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        
        vector<vector<int>> adj (N + 1);
        vector<int> group (N + 1, -1);
        
        for (auto &v : dislikes) {
            adj[v[0]].push_back(v[1]);
            adj[v[1]].push_back(v[0]);
        }
        
        int color {0};
        for (int i = 1; i <= N; i++) {
            dfs(adj, group, color, i);
            for (int j = 0; j < adj[i].size(); j++) {
                if (group[i] == group[adj[i][j]])
                    return false;
            }
            color = !color;
        }
        return true;
    }
};
