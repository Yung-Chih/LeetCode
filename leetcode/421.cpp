#include <vector>
#include <iostream>
#include <cstdio>
#include <bitset>
#include <algorithm>
#include <cassert>
using namespace std;
class Solution {

private:
    int findMaxXOR(vector<int>& X, int mask, int L0, int R0, int L1, int R1){
        if( R0 - L0 == 1 || R1 - L1 == 1 || mask == 0){
            int ans = 0;
            for(int i=L0; i<R0; i++){
                for(int j=L1; j<R1; j++){
                    ans = max(ans, X[i] ^ X[j]);
                }
            }
            return ans;
        }
        int d[2];
        d[0] = this->devide(X, mask>>1, L0, R0);
        d[1] = this->devide(X, mask>>1, L1, R1);

        bool flag[2];
        flag[0] = (d[0] == L0 || d[0] == R0);
        flag[1] = (d[1] == L1 || d[1] == R1);

        
        if( flag[0] && flag[1] ){
            return findMaxXOR(X, mask>>1, L0, R0, L1, R1);
        }
        else if( flag[0] && !flag[1] ){
            if( d[0] == R0 )
                return findMaxXOR(X, mask>>1, L0, R0, d[1], R1);
            else
                return findMaxXOR(X, mask>>1, L0, R0, L1, d[1]);
        }
        else if( !flag[0] && flag[1] ){
            if( d[1] == R1 )
                return findMaxXOR(X, mask>>1, d[0], R0, L1, R1);
            else
                return findMaxXOR(X, mask>>1, L0, d[0], L1, R1);
        }
        else{
            return max(findMaxXOR(X, mask>>1, L0, d[0], d[1], R1),
                       findMaxXOR(X, mask>>1, d[0], R0, L1, d[1]));
        }
    }

    int devide(vector<int>& X, int mask, int L, int R){
        while( L+1 < R ){
            int mid = (L+R)/2;
            if( (X[mid] & mask) == 0 ) L = mid;
            else R = mid;
        } 
        return (X[L] & mask) != 0 ? L : R;
    }
    // int devide(vector<int>& X, int mask, int L, int R){
    //     int i = L;
    //     while( i < R && (X[i] & mask) == 0 ) i++;
    //     return i;
    // }

public:
    int findMaximumXOR(vector<int>& nums) {
        vector<int> X, B[2];
        X.insert(X.end(), nums.begin(), nums.end());
        std::sort(X.begin(), X.end());

        std::vector<int>::iterator it;
        it = std::unique (X.begin(), X.end());
        X.resize( std::distance(X.begin(),it) );

        if( X.size() == 1 ) return 0;

        // for(int i=0; i<X.size(); i++){
        //     bitset<32> b(X[i]);
        //     printf("%d:\t%s\n", X[i], b.to_string().c_str() );
        // }
        // printf("\n");


        int mask = 1 << 30, d = devide(X, mask, 0, X.size());
        while( d == 0 || d == X.size() ){
            mask = mask >> 1;
            d = devide(X, mask, 0, X.size());
            // cout << d << endl;
        }
        cout << mask << ' ' <<d << endl;
        return this->findMaxXOR(X, mask, 0, d, d, X.size());
    }
};

int main(){
    vector<int> nums = {4,5,6};
    // vector<int> nums = {14,70,53,83,49,91,36,80,92,51,66,70};
    Solution sol;
    cout << sol.findMaximumXOR(nums) << endl;
    return 0;
}