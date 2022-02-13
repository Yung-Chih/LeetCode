#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int s = 0;
        map<int, vector<int>> sum_pos;
        sum_pos[0].emplace_back(-1);
        for(int i=0; i<nums.size(); i++){
            s += nums[i];
            sum_pos[s].emplace_back(i);
        }
        
        int res = 0;
        for( auto p : sum_pos ){
            auto it = sum_pos.find( k + p.first );
            cout << p.first << ": ";
            for(int x : p.second){
                cout << ' ' << x;
            }
            cout << endl;
            if( it == sum_pos.end() ) continue;
            cout << p.first << " & " << it->first << endl;
            if( p.first != it->first ){
                for( int x : p.second ){
                    res += it->second.end() - lower_bound(it->second.begin(), it->second.end(), x );
                }
            }
            else{
                for( int i=0; i<p.second.size(); i++ ){
                    res += p.second.size() - 1 - i;
                }
            }
        }
        return res;
    }
};

int main(){
    vector<int> nums = {1,1,1,2,3,4,5,1,2,-1,-2,-3,-4,0,0,0,0,0,0,0,0};
    int k = 0;
    Solution sol;
    cout << sol.subarraySum(nums, k) << endl;
    return 0;
}