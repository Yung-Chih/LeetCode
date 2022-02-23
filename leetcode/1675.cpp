#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int take_op(int x){
        return (x%2) ? x * 2 : x / 2;
    }
public:
    int minimumDeviation(vector<int>& nums) {
        set<int> S;
        for(int& x : nums){
            S.emplace(x * ((x%2) + 1) );
        }
        int res = *S.rbegin() - *S.begin();
        while( *S.rbegin() % 2 == 0 ){
            int x = *S.rbegin();
            S.erase(x);
            S.emplace( take_op(x) );
            res = min(res, *S.rbegin() - *S.begin());
        }
        return res;
    }
};

int main(){
    // vector<int> nums = {1,2,3,4,5,20};
    vector<int> nums = {123, 444};
    Solution sol;
    cout << sol.minimumDeviation(nums) << endl;
}

/*
4k < - > 2k < - > k
2k + 1 < - > 2(2k+1)

123 444
123 222
123 111
*/