/* 1192. Critical Connections in a Network
https://leetcode.com/problems/critical-connections-in-a-network/

There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.
A critical connection is a connection that, if removed, will make some server unable to reach some other server.
Return all critical connections in the network in any order.

Example 1:

Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
 
Constraints:

1 <= n <= 10^5
n-1 <= connections.length <= 10^5
connections[i][0] != connections[i][1]
There are no repeated connections.
*/
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>> &graph, vector<vector<int>> &res, vector<int> &disc, vector<int> &low, int u, int parent, int &id) {
        
        disc[u] = low[u] = ++id;
        
        for (int j = 0; j < graph[u].size(); j++) {
            int v = graph[u][j];
            
            if (v == parent)
                continue;
            
            if (disc[v] == -1) {
                dfs(graph, res, disc, low, v, u, id);
                low[u] = min(low[u], low[v]);
                
                if (low[v] > disc[u])   // u - v is critical
                    res.push_back({u, v});
            } else { // if v is visited before, and is not parent of u, update low[u], cannot use low[v] because u is not subtree of v
                low[u] = min(low[u], disc[v]);
            }
        }
    }
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        
        vector<int> disc (n, -1);
        vector<int> low (n, 0);
        vector<vector<int>> graph (n, vector<int>());
        vector<vector<int>> res;
        
        for (auto &conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        int id = 0;
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1)
                dfs(graph, res, disc, low, i, i, id);
        }
        return res;
    }
};
