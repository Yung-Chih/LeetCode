#include <vector>
#include <cstdio>

using namespace std;
class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int res = 0;
        for( vector<int>& customer : accounts){
            int sum = 0;
            for(int& x : customer) sum += x;
            res = max(res, sum);
        }
        return res;
    }
};