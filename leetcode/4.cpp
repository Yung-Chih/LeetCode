#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
private:
    int lower_rank(int& x, vector<int>& num){
        // 0-base rank
        return ( num.size() ) ? lower_bound(num.begin(), num.end(), x) - num.begin() : 0;
    }
    int upper_rank(int& x, vector<int>& num){
        return ( num.size() ) ? upper_bound(num.begin(), num.end(), x) - num.begin() : 0;
    }
    double search_rank(int target, vector<int>& nums1, vector<int>& nums2){
        int L1 = 0, R1 = nums1.size();
        int L2 = 0, R2 = nums2.size();
        int mid, rk, other_rk;
        while( L1+1 < R1 ){
            // target in [L1, R1)
            mid = (L1+R1) / 2;
            other_rk = lower_rank(nums1[mid], nums2);
            rk = mid + other_rk;
            if( rk <= target ){
                // target in (mid, R1)
                L1 = mid;
                L2 = other_rk;
                if( rk == target ) return nums1[mid];
            }
            else{
                R1 = mid;
                R2 = other_rk;
            }
        }

        if( R1 && L1 + lower_rank(nums1[L1], nums2) == target){
            return nums1[L1];
        }

        while( L2+1 < R2 ){
            // target in [L, R)
            mid = (L2+R2) / 2;
            other_rk = upper_rank(nums2[mid], nums1);
            rk = mid + other_rk;

            if( rk <= target ){
                L2 = mid;
                if( rk == target) return nums2[mid];
            }
            else{
                R2 = mid;
            }
        }
        if( R2 && L2 + upper_rank(nums2[L2], nums1) == target){
            return nums2[L2];
        }
        return -1e9;
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int N = nums1.size() + nums2.size();
        double res = this->search_rank(N/2, nums1, nums2);
        if( !(N & 1) ){
            res = (res + this->search_rank(N/2-1, nums1, nums2) ) / 2.0;
        }
        return res;
    }
};

int main(){
    vector<int> nums1 = {};
    vector<int> nums2 = {2, 3};
    // cout << (upper_bound(nums1.begin(), nums1.end(), 0) - nums1.begin()) << endl;
    // cout << (lower_bound(nums1.begin(), nums1.end(), 0) - nums1.begin()) << endl;

    Solution sol;
    cout << sol.findMedianSortedArrays(nums1, nums2) << endl;

    return 0;
}