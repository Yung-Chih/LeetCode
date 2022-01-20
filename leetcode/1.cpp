#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;
class Solution {
public:
    int binary_search(int L, int R, const vector<pair<int, int>>& num_id, const int& target){
        while( L < R ){ // [L, R]
            int mid = (L+R) / 2;
            if( num_id[mid].first < target ){
                L = mid+1; // [mid+1, R]
            }
            else{
                R = mid; // [L, mid]
            }
        }
        if( num_id[L].first != target )
            return -1;
        else
            return L;
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        using pii = pair<int, int>;
        int N = nums.size();
        vector<pii> num_id;
        for(int i=0; i<N; i++){
            num_id.emplace_back(nums[i], i);
        }
        std::sort(num_id.begin(), num_id.end());

        vector<int> res(2);
        for(int i=0; i<N; i++){
            int x = num_id[i].first, y = target - x;
            
            int yid = this->binary_search(i+1, N-1, num_id, y);
            if( yid != -1 ){
                res[0] = num_id[i].second;
                res[1] = num_id[yid].second;
                return res;
            }
        }
        return res;
    }
};

int main(){
    vector<int> nums = {3,3};
    int target = 6;

    Solution sol;
    vector<int> ans = sol.twoSum(nums, target);
    for(int i=0; i<ans.size(); i++){
        cout << ans[i] << endl;
    }
}