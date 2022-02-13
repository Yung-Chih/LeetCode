#include <string>
#include <limits>
#include <iostream>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int val = 0;
        int sign = 1;
        int i = 0;
        while( i < s.size() && isspace(s[i]) ){
            i++;
        }
        if( i == s.size() || (s[i] != '+' && s[i] != '-' && !isdigit(s[i])) ){
            return 0;
        }

        if( s[i] == '-' || s[i] == '+' ){
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        while( i < s.size() && isdigit(s[i]) ){
            int d = sign * (s[i] - '0');
            if( sign == 1 ){
                if( val <= (INT32_MAX - d) / 10 )
                    val = val * 10 + d;
                else
                    val = INT32_MAX;
            }
            else{
                if ( val >= (INT32_MIN - d) / 10)
                    val = val * 10 + d;
                else
                    val = INT32_MIN;
            }
            i++;
        }

        return val;
    }
};

int main(){
    string s;
    Solution sol;
    while(getline(cin, s)){
        cout << sol.myAtoi(s) << endl;
    }
}