class Solution {
public:
    int addDigits(int num) {
        if( num == 0 ) return 0;
        return (num-1) % 9 + 1;
    }
    int addDigits_ans(int num) {
        if( num < 10 )
            return num;
        else
            return addDigits_ans(num/10 + num%10);
    }
};

#include <cstdio>
#include <limits>
#include <cassert>
int main(){
    Solution sol;
    printf("%d\n", sol.addDigits(0));
    
    for(int i=0; i<= __INT32_MAX__; i++){
        if( i % 100000 == 0 )
            printf("%d\n", i);
        assert( sol.addDigits(i) == sol.addDigits_ans(i) );
    }
    printf("Success");
}