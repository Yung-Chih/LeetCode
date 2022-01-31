#include <vector>
using namespace std;
#include <iostream>
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        if( k == 0 ) return;
        vector<int> tmp;
        while(k--){
            tmp.emplace_back( nums.back() );
            nums.pop_back();
        }
        nums.insert(nums.begin(), tmp.rbegin(), tmp.rend());
    }
};

int main(){
    Solution sol;
    vector<int> nums = {1,2,3};
    cout << nums[0] << ' ' << nums[1] << ' ' << nums[2] << endl;
    sol.rotate(nums, 1);
    cout << nums[0] << ' ' << nums[1] << ' ' << nums[2] << endl;
    return 0;
}