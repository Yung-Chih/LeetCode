#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // Unique element appears at most twice.
        // The relative order of the elements should be kept the same.
        int k = 0;
        for(int i=1; i<nums.size(); i++){
            if( nums[k] != nums[i] ){
                nums[++k] = nums[i];
            }
            else if( k == 0 || nums[k] != nums[k-1] ){
                nums[++k] = nums[i];
            }
        }

        return k+1;
    }
};

int main(){
    Solution sol;
    // vector<int> nums = {1,1,1,2,2,2,2,3,4,4,4};
    // vector<int> nums = {1,1,2,2,3};
    vector<int> nums = {1};
    for(int i=0; i<nums.size(); i++){
        cout << nums[i] << ' ';
    }
    cout << endl;
    int k = sol.removeDuplicates(nums);
    for(int i=0; i<k; i++){
        cout << nums[i] << ' ';
    }
    cout << endl;
    return 0;
}