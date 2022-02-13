#include <vector>
#include <unordered_map>
#include <cstdio>
using namespace std;
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        int ans = 0;
        unordered_map<int, int> cnt;
        for(int i=0; i<nums.size(); i++){
            cnt[nums[i]]++;
        }
        if( k == 0 ){
            for(auto p : cnt){
                ans += p.second >= 2;
            }
        }
        else{
            for(auto p : cnt){
                ans += cnt.count(p.first+k);
            }
        }
        return ans;
    }
};

int main(){
    vector<int> nums = {1,3,1,3,1,3,1,4,1,5};
    int k = 2;
    Solution sol;
    printf("%d\n", sol.findPairs(nums, k));
}