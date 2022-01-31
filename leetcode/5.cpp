#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    string longestPalindrome(string s) {
        int N = s.size();
        string ans = "";

        // k <- [i] -> k
        for(int i=0; i<N; i++){
            int k = 0;
            while( k <= i && i+k < N && s[i-k] == s[i+k] ) k++;
            if( ans.size() < 2*k - 1 ){
                ans = s.substr(i-k+1, 2*k-1);
            }
        }
        // k <- [i, i+1] -> k
        for(int i=0; i<N-1; i++){
            if( s[i] != s[i+1] ) continue;
            int k = 0;
            while( k <= i && i+k+1 < N && s[i-k] == s[i+k+1] ) k++;
            if( ans.size() < 2*k ){
                ans = s.substr(i-k+1, 2*k);
            }
        }
        return ans;
    }
};

int main(){
    string s;
    cin >> s;
    Solution sol;
    cout << sol.longestPalindrome(s) << endl;
    return 0;
}