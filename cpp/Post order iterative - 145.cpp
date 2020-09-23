/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        TreeNode* last = nullptr;

        while (cur != nullptr || !st.empty()) {
            if (cur) {
                st.push(cur);
                cur = cur->left;
            } else {
                TreeNode *node = st.top();
                if (node->right && last != node->right) {
                    cur = node->right;
                } else {
                    res.push_back(node->val);
                    st.pop();
                    last = node;
                }
            }
        }
        return res;
    }
};