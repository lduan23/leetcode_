/* 317. Shortest Distance from All Buildings
https://leetcode.com/problems/shortest-distance-from-all-buildings/

You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:

Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 7 

Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
             the point (1,2) is an ideal empty land to build a house, as the total 
             travel distance of 3+3+1=7 is minimal. So return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
*/

#include <vector>
#include <queue>
#define INT_MAX 1000000
using namespace std;

class Solution {
public:
    vector<int> dx {-1, 1, 0, 0};
    vector<int> dy {0, 0, -1, 1};
    
    void bfs(vector<vector<int>> &grid, vector<vector<int>> &vec, bool &vec_empty, int i, int j, const int m, const int n) {
        queue<pair<int, int>> q;
        q.push({i, j});
        vec[i][j] = 0;
        
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            
            for (int t = 0; t < 4; t++) {
                int u = x + dx[t];
                int v = y + dy[t];
                
                if (u >= 0 && u < m && v >= 0 && v < n && grid[u][v] == 0 && vec[u][v] == -1) {
                    vec[u][v] = vec[x][y] + 1;
                    q.push({u, v});
                    vec_empty = false;
                }
            }
        }
        accessCheck(grid, vec);
    }
    
    void accessCheck(vector<vector<int>> &grid, vector<vector<int>> &vec) {
		// if a building is not accessible anymore, mark as '2' in grid
        for (int i = 0; i < vec.size(); i++) {
            for (int j = 0; j < vec[0].size(); j++) {
                if (grid[i][j] == 0 && vec[i][j] == -1)
                    grid[i][j] = 2;
            }
        }
    }
    
    int shortestDistance(vector<vector<int>>& grid) {
        
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        
		// bfs starts from '1'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1)
                    q.push({i, j});
            }
        }
        
        int size = q.size();
        vector<vector<vector<int>>> dist;
        
		// run bfs from all '1'
        while (!q.empty()) {
            vector<vector<int>> vec (m, vector<int>(n, -1));
            bool vec_empty {true};  // flag for checking if no '0' in grid, return -1
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            
            bfs(grid, vec, vec_empty, x, y, m, n);
            
            if (vec_empty)
                return -1;
            else
                dist.push_back(vec);
        }
        
		// find the min sum distance of each {i,j} from every bfs results
        int shortest {INT_MAX};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int distance {0};
                    for (int k = 0; k < size; k++) {
                        distance += dist[k][i][j];
                    }
                    shortest = min(shortest, distance);
                }
            }
        }
        return shortest;
    }
};