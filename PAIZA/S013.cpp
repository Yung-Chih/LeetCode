#include <bits/stdc++.h>

using namespace std;

int N;
int c_f, c_b;
int init_status, target_vis;
int dp[8][1 << 8][1 << 8];
int ptr[8][1 << 8][1 << 8];

int mask[8];

int cost(int from, int to){
    assert(from != to);
    if( from < to ) return c_f;
    if( from > to ) return c_b;
    return INT_MAX;
}

int calc(int from, int status, int vis){
    if( dp[from][status][vis] != -1 )
        return dp[from][status][vis];
    if( from == N-1 && vis == target_vis ){// visit all && return to start
        ptr[from][status][vis] = -1;
        return dp[from][status][vis] = 0;
    }
    
    dp[from][status][vis] = 1e9+9;
    for(int i=0; i<N; i++){
        if( from == i ) continue;
        if( ((1 << i) & status) == 0 ) continue;
        int next_status = status ^ mask[i];
        int next_vis = vis | (1 << i);
        int child_res = calc(i, next_status, next_vis);
        int val = child_res + cost(from, i);
        if( val < dp[from][status][vis] ){
            dp[from][status][vis] = val;
            ptr[from][status][vis] = i;
        }
    }
    return dp[from][status][vis];
}

int main(void){
    cin >> N;
    cin >> c_f >> c_b;

    for(int i=N-1; i>=0; i--){
        mask[i] = ( 1 << i );
    }
    for(int i=1; i<N; i++){
        mask[i] |= mask[i-1];
    }
    target_vis = mask[N-1];
    for(int i=0; i<N; i++){
        mask[i] = mask[i] ^ mask[N-1];
        // printf("mask[%d]: %0x\n", i, mask[i]);
    }

    init_status = 0;
    for(int i=0; i<N; i++){
        char c;
        cin >> c;
        init_status |= ( c == 's' ) ? ( 1 << i ) : 0;
    }

    memset(dp, -1, sizeof(dp));
    memset(ptr, -1, sizeof(ptr));
    
    int min_cost = calc(N-1, init_status, 0);
    cout << "min cost: " << min_cost << endl;

    int cur = N-1, s = init_status, v = 0;
    vector<int> path;
    while( cur != -1 ){
        path.emplace_back(cur + 1);
        cur = ptr[cur][s][v];
        s = s ^ mask[cur];
        v = v | (1 << cur);
    }
    cout << path[0];
    for(int i=1; i<path.size(); i++){
        cout << ' ' << path[i];
    }
    cout << endl;

    return 0;
}