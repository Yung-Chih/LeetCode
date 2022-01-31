#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int EatingHours(vector<int>& piles, int speed){
        int h = 0;
        for(int i=0; i<piles.size(); i++){
            h += (piles[i] % speed) ? piles[i] / speed + 1 : piles[i] / speed;
        }
        return h;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int L = 1, R = *std::max_element(piles.begin(), piles.end());
        // k in [L, R]
        while( L < R ){
            int mid = (L+R)/2;
            int k = this->EatingHours(piles, mid);
            cout << L << ' ' << R << ' ' << mid << ' ' << k << endl;
            if( k > h ){ // speed too slow
                L = mid + 1;
            }
            else{
                R = mid;
            }
        }
        return L;
    }
};

int main(){
    vector<int> piles = {1,1,1,1,1};
    int h = 8;

    Solution sol;
    cout << sol.minEatingSpeed(piles, h) << endl;
    return 0;
}