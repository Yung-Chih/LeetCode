#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
private:
    void inorder(TreeNode* r, vector<int>& v){
        if( r == nullptr ) return;
        inorder(r->left, v);
        v.emplace_back(r->val);
        inorder(r->right, v);
    }
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> v1, v2;
        inorder(root1, v1);
        inorder(root2, v2);
        vector<int> res(v1.size() + v2.size());
        
        int i = 0, j = 0, k = 0;
        while( i < v1.size() || j < v2.size() ){
            if( i == v1.size() ){
                res[k++] = v2[j++];
            }
            else if( j == v2.size() ){
                res[k++] = v1[i++];
            }
            else if( v1[i] <= v2[j] ){
                res[k++] = v1[i++];
            }
            else{
                res[k++] = v2[j++];
            }
        }
        return res;
    }
};