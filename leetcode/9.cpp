#include <string>
#include <sstream>
#include <iostream>
using namespace std;
class Solution {
public:
    bool isPalindrome(int x) {
        string s;
        stringstream ss;

        ss << x;
        ss >> s;
        for(int i=0; i<s.size()/2; i++){
            if( s[i] != s[s.size()-i-1] ) return false;
        }
        return true;
    }
};

int main(){
    int x;
    Solution sol;
    while(cin>>x){
        cout << sol.isPalindrome(x) << endl;
    }
}