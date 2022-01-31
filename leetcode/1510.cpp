#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> win(n+1, false); // win[n] = true iff first-hand wins with n stone.
        win[0] = false; // Alice lose when n = 0
        for(int i=1; i<=n; i++){
            bool flag;
            for(int k=1; k*k <= i; k++){
                // Alice try k*k
                // Alice wins iff one of win[i-k*k] = false
                if( win[i-k*k] == false ){
                    win[i] = true;
                }
            }
        }
        return win[n];
    }
};

int main(){
    Solution sol;
    for(int i=0; i<10; i++){
        cout << i << ' ' << sol.winnerSquareGame(i) << endl;
    }
    return 0;
}