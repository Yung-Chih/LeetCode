#include<bits/stdc++.h>

using namespace std;



int main(){
    int N;
    char digit[10];
    bool first = true;
    while(true){
        cin >> N;
        if( N == 0 ) break;

        for(int i=0; i<10; i++){
            digit[i] = '0' + i;
        }

        if( !first ) cout << endl;

        bool has_sol = false;
        do{
            std::string low(digit, 5), up(digit+5, 5);
            int low_num = stoi(low), up_num = stoi(up);
            if( up_num / low_num == N && up_num % low_num == 0 ){
                printf("%s / %s = %d\n", up.c_str(), low.c_str(), N);
                has_sol = true;
            }
        }while( std::next_permutation(digit, digit+10) );
        if( !has_sol ){
            printf("There are no solutions for %d.\n", N);
        }
        first = false;
    }
    return 0;
}