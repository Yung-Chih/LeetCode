#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
private:
    void dfs(vector<int>& cur, int k, vector<int>& candidates, int target, vector<vector<int>>& res){
        if( target == 0 ){
            res.emplace_back(cur);
            return;
        }
        if( target < 0 ) return;
        for(int i=k; i<candidates.size(); i++){
            cur.emplace_back( candidates[i] );
            dfs(cur, i, candidates, target-candidates[i], res);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> cur;
        sort(candidates.begin(), candidates.end());
        dfs(cur, 0, candidates, target, res);
        return res;
    }
};
int main(){
    vector<int> nums = {2,3,6,7};
    int target;
    Solution sol;
    while(cin>>target){
        vector< vector<int> > res = sol.combinationSum(nums, target);
        for(auto v : res){
            for(int x : v){
                cout << x << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}