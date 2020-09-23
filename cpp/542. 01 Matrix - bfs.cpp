/* 542. 01 Matrix
https://leetcode.com/problems/01-matrix/

Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

Example 1:

Input:
[[0,0,0],
 [0,1,0],
 [0,0,0]]

Output:
[[0,0,0],
 [0,1,0],
 [0,0,0]]
Example 2:

Input:
[[0,0,0],
 [0,1,0],
 [1,1,1]]

Output:
[[0,0,0],
 [0,1,0],
 [1,2,1]]
 

Note:

The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.
*/
#include <vector>
#include <queue>
using namespace std;

class Solution {
private:
    vector<int> dx {-1, 1, 0, 0};
    vector<int> dy {0, 0, -1, 1};
    
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<vector<int>> output (m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0 && output[i][j] == -1) {
                    output[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        
        while (!q.empty()) {
            
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            for (int t = 0; t < 4; t++) {
                
                int r = row + dx[t];
                int c = col + dy[t];
                
                if (r >= 0 && r < m && c >= 0 && c < n && matrix[r][c] == 1 && output[r][c] == -1) {
                    output[r][c] = output[row][col] + 1;
                    q.push({r, c});
                }
            }
        }
        
        return output;
    }
};