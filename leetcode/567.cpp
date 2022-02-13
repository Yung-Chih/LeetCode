#include <string>
#include <iostream>
using namespace std;


class Solution {
public:
    bool cnt_equal(int cnt[2][26]){
        for(int i=0; i<26; i++){
            if( cnt[0][i] != cnt[1][i] ) return false;
        }
        return true;
    }
    bool checkInclusion(string s1, string s2) {
        if( s1.size() > s2.size() ) return true;
        int cnt[2][26];
        for(int i=0; i<26; i++){
            cnt[0][i] = cnt[1][i] = 0;
        }

        for(char c : s1){
            cnt[0][ c - 'a' ]++;
        }
        for(int i=0; i< s1.size(); i++){
            cnt[1][ s2[i] - 'a' ]++;
        }

        for(int i=s1.size(); i<s2.size(); i++){
            if( cnt_equal(cnt) ) return true;
            cnt[1][ s2[i] - 'a' ]++;
            cnt[1][ s2[i-s1.size()] - 'a' ]--;

        }
        return cnt_equal(cnt);
    }
};

int main(){
    Solution sol;
    cout << sol.checkInclusion("ab", "eidbaooo") << endl;
}