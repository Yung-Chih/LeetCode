#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> ZAG(numRows, "");
        int i = 0, dir = -1;
        for(const char& c : s ){
            ZAG[i] += c;
            if( i == 0 || i == numRows - 1 ) dir = -dir;
            i = i + dir;
        }
        string ans;
        for(const string& z : ZAG ){
            ans += z;
        }
        return ans;
    }
};