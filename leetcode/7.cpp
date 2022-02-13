#include <limits>
#include <algorithm>
#include <iostream>
class Solution {
public:
    int reverse(int x) {

        int y = 0;
        while( x > 0 ){
            if( y <= ( INT32_MAX - x % 10 ) / 10 ){
                y = y * 10 + x % 10;
                x = x/10;
            }
            else return 0;
        }
        while( x < 0 ){
            if( y >= ( INT32_MIN - x % 10 ) / 10){
                y = y * 10 + x % 10;
                x = x/10;
            }
            else return 0;
        }
        return y;
        
    }
};

int main(){
    int x;
    Solution sol;
    while( std::cin >> x ){
        std::cout << sol.reverse(x) << std::endl;
    }
}