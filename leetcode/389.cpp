#include <string>
using namespace std;
class Solution {
public:
    char findTheDifference(string s, string t) {
        char cnt_s[26] = {};
        for(char& c : s){
            cnt_s[c-'a']++;
        }
        for(char& c : t){
            cnt_s[c - 'a']--;
        }
        for(int i=0; i<26; i++){
            if( cnt_s[i] == -1 )
                return 'a' + i;
        }
        return '-';
    }
};