#include<bits/stdc++.h>

using namespace std;


int main(void){
    int in;
    unsigned int x, y;
    int mask[4], shift[4];
    for(int i=0; i<4; i++){
        mask[i] = 0xFF << (8*i);
        shift[i] = 24 - i * 16;
    }
    while(cin >> in){
        x = 0 | in;
        y = 0;
        for(int i=0; i<4; i++){
            if( shift[i] > 0 ){
                y |= ( x & mask[i] ) << shift[i];
            }
            else{
                y |= ( x & mask[i] ) >> abs(shift[i]);
            }
        }


        // printf("x: %08X\ny: %08X\n", x, y);
        std::cout << (int)x << " converts to " << (int)y << endl;
    }
    return 0;
}

/*
123456789
-123456789
1
16777216
20034556
*/