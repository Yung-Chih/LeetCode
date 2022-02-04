#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // For each price[i], select the min price in price[...i-1]
        int res = 0, min_p = prices[0];
        for(int i=1; i<prices.size(); i++){
            res = max( res, prices[i] - min_p );
            min_p = min( min_p, prices[i] );
        }
        return res;
    }
};

int main(){
    vector<int> prices = {7,1,5,3,6,4};
    Solution sol;
    cout << sol.maxProfit(prices) << endl;
    return 0;
}