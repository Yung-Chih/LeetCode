#include <string>
#include <set>
#include <iostream>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i = 0, j = 0, k = 0;
        int cnt[128] = {};
        while( i < s.size() && j < s.size()){

            // left shrink
            while( cnt[s[j]] ){ // i <= j
                cnt[s[i++]]--;
            }

            // right append
            while( j < s.size() && !cnt[s[j]] ){
                cnt[s[j++]]++;
            }
            k = max(k, j-i);
        }
        return k;
    }
};

int main(){
    string s;
    cin >> s;
    Solution sol;
    cout << sol.lengthOfLongestSubstring(s) << endl;
    return 0;
}