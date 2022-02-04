#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> m;
        m[0] = -1;
        int res = 0, sum = 0;
        for(int i=0; i<nums.size(); i++){
            sum += nums[i] ? 1 : -1;
            auto it = m.find( sum );
            if( it != m.end() ){
                // cout << it->second+1 << " ~ " << i << endl;
                res = max(res, i - it->second);
            }
            if( m.find(sum) == m.end() ){
                m[sum] = i;
            }
        }
        return res;
    }
};

int main(){
    Solution sol;
    vector<int> nums[4] = { {0, 1}, {0, 1, 1, 0}, {0,1,0,1}, {1,1,1,0,0,1,1,1} };
    for(int i=0; i<4; i++){
        cout << sol.findMaxLength(nums[i]) << endl;
    }
    return 0;
}