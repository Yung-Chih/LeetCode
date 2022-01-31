#include <string>
#include <cstdio>
using namespace std;
class Solution {
public:
    bool detectCapitalUse(string word) {
        if( word.size() == 0 ) return false;
        bool first = isupper(word[0]);
        bool other[2] = {true, true};
        for(int i=1; i<word.size(); i++){
            if( isupper(word[i]) ){
                other[0] = false;
            }
            else{
                other[1] = false;
            }
        }
        return (first && (other[0] || other[1])) || (!first && other[0]);
    }
};