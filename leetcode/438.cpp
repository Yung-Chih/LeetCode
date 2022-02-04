#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool equal(int cnt_s[26], int cnt_p[26]){
        for(int i=0; i<26; i++){
            if( cnt_s[i] != cnt_p[i] ) return false;
        }
        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        if( s.size() < p.size() ) return vector<int>();

        int cnt_s[26] = {0}, cnt_p[26] = {0};
        for(char& c : p){
            cnt_p[c - 'a']++;
        }
        for(int i=0; i<p.size(); i++){
            cnt_s[s[i]-'a']++;
        }

        vector<int> res;
        for(int i=0; i<s.size()-p.size(); i++){
            if( equal(cnt_s, cnt_p) )
                res.emplace_back(i);
            cnt_s[ s[i] - 'a' ]--;
            cnt_s[ s[i+p.size()] - 'a' ]++;
        }
        if( equal(cnt_s, cnt_p) ) res.emplace_back(s.size()-p.size());
        return res;
    }
};