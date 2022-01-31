#include <bits/stdc++.h>

using namespace std;
#define MAX_N 18
int N;
int kx, ky, cx, cy;
int dp[MAX_N][MAX_N][MAX_N][MAX_N];
bool vis[MAX_N][MAX_N][MAX_N][MAX_N];

int dkx[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
int dky[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
int dcx[4] = {-1, -1,  1, 1}; 
int dcy[4] = {-1,  1, -1, 1};

bool valid(int x, int y){
    return ( 0 <= x && x < N && 0 <= y && y < N ); 
}



int calc(int kx, int ky, int cx, int cy){
    vis[kx][ky][cx][cy] = true;
    // printf("(%d, %d) (%d, %d) start\n",kx, ky, cx, cy);

    if( abs(kx - cx) <= 1 && abs(ky - cy) <= 1){
        // printf("(%d, %d) (%d, %d): %d end\n",kx, ky, cx, cy, 1);
        return dp[kx][ky][cx][cy] = 1;
    }

    dp[kx][ky][cx][cy] = 1;
    int nkx, nky, nd = 1e9;
    for(int i=0; i<8; i++){
        int x = kx + dkx[i];
        int y = ky + dky[i];
        if( !valid(x, y) ) continue;
        int d = abs(x - cx) + abs(y - cy);
        if( d < nd && !(abs(x-cx) == 1 && abs(y - cy) == 1) ){
            nkx = x, nky = y;
            nd = d;
        }
    }

    // printf("nkx, nky: %d, %d\n", nkx, nky);
    for(int j=0; j<4; j++){
        int ncx = cx + dcx[j];
        int ncy = cy + dcy[j];
        if( !valid(ncx, ncy) ) continue;
        if( vis[nkx][nky][ncx][ncy] ) continue;
        // printf("\t ncx, ncy: %d, %d\n", ncx, ncy);
        int res = calc(nkx, nky, ncx, ncy);
        dp[kx][ky][cx][cy] = max(dp[kx][ky][cx][cy], res + 1);
    }
    // printf("(%d, %d) (%d, %d): %d end\n",kx, ky, cx, cy, dp[kx][ky][cx][cy]);
    return dp[kx][ky][cx][cy];
}

int main(void){
    cin >> N;
    cin >> kx >> ky;
    cin >> cx >> cy;

    memset(dp, -1, sizeof(dp));

    cout << calc(kx, ky, cx, cy) << endl;
    return 0;
}

/*
5
0 2
4 0
*/