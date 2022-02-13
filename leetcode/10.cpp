#include <string>
#include <iostream>
using namespace std;

class Solution {
private:
    bool Match(int i, int j, const string& s, const string& p){
        if( p[j] == '$' ){
            return s[i] == '$';
        }
        if( s[i] == '$' ){
            if( p[j+1] == '*' ) // s[:i] match to p[:j-1], skip p[j] *
                return Match(i, j+2, s, p);
            else
                return false;
        }

        if( p[j+1] == '*' ){
            // skip p[j] or use one p[j](preserve *)
            if( s[i] == p[j] || p[j] == '.'){
                return Match(i, j+2, s, p) | Match(i+1, j, s, p);
            }
            else{
                return Match(i, j+2, s, p);
            }
        }
        
        // Normal case
        if( s[i] == p[j] || p[j] == '.' ){
            return Match(i+1, j+1, s, p);
        }
        else{
            return false;
        }
    }
public:
    bool isMatch(string s, string p) {
        s = s + "$", p = p + "$";
        return Match(0, 0, s, p);
    }
};

int main(){
    string s, p;
    Solution sol;
    while( cin >> s >> p ){
        cout << sol.isMatch(s, p) << endl;
    }
    return 0;
}