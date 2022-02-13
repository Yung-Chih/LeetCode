#include <string>
using namespace std;
class Solution {
private:
    int value(const char& c){
        switch (c)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
        }
    }
public:
    int romanToInt(string s) {
        int res = 0;
        s = s + '0';
        for(int i=0; i<s.size()-1; i++){
            if( value(s[i]) < value(s[i+1]) ){
                res += value(s[i+1]) - value(s[i]);
                i++;
            }
            else{
                res += value(s[i]);
            }
        }
        return res;
    }
};