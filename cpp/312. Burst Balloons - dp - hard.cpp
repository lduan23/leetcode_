/* 312. Burst Balloons
https://leetcode.com/problems/burst-balloons/

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
Find the maximum coins you can collect by bursting the balloons wisely.

Note:
You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167 
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> num (n + 2);
        
        for (int i = 0; i < n; i++) {
            num[i + 1] = nums[i];
        }
        
        num[0] = num[n + 1] = 1;
        vector<vector<int>> dp (n + 2, vector<int>(n + 2, 0));
        
        for (int k = 2; k < n + 2; k++) {
            for (int left = 0; left < n + 2 - k; left++) {
                int right = left + k;
                for (int i = left + 1; i < right; i++) {
                    dp[left][right] = max(dp[left][right], num[left] * num[i] * num[right] + dp[left][i] + dp[i][right]);
                }
            }
        }
        return dp[0][n + 1];
    }
};


class Solution_dfs {
public:
    int dfs(vector<int> &num, vector<vector<int>> &dp, int l, int r) {
        if (l + 1 == r)
            return 0;
        
        if (dp[l][r] > 0)
            return dp[l][r];
        
        int res {0};
        for (int k = l + 1; k < r; k++) {
            res = max(res, num[l] * num[k] * num[r] + dfs(num, dp, l, k) + dfs(num, dp, k, r));
        }
        dp[l][r] = res;
        return res;
    }
    
    int maxCoins(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> num (n + 2);
        
        for (int i = 0; i < n; i++)
            num[i+1] = nums[i];
        
        num[0] = 1; 
        num[n+1] = 1;
        vector<vector<int>> dp (n + 2, vector<int>(n + 2, 0));
        
        return dfs(num, dp, 0, n + 1);
    }
};