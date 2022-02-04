#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        int N = nums1.size();
        vector<int> nums12(N*N);

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                nums12[i*N+j] = nums1[i] + nums2[j];
            }
        }

        sort(nums12.begin(), nums12.end());

        int cnt = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cnt += upper_bound(nums12.begin(), nums12.end(), -nums3[i] - nums4[j]) -  lower_bound(nums12.begin(), nums12.end(), -nums3[i] - nums4[j]);
            }
        }
        return cnt;
    }
};