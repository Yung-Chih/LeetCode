#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
using tiii = tuple<int, int, int>;
using pii = pair<int, int>;
#define MAX_N (5 * (int)1e5)

int n_digit(int x, int n){
    if( n == 1 ) return x % 10;
    else return n_digit(x/10, n-1);
}

int main(void){
    int T = 100000;
    printf("%d\n", T);
    for(int i=0; i<T; i++){
        printf("5\n");
        for(int n=5; n>=1; n--) printf("%d", n_digit(i, n));
        printf("\n");
    }
    return 0;
}