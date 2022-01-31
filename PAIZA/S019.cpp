#include <bits/stdc++.h>

using namespace std;
#define MAX_N 2000

using tiii = tuple<int, int, int>;

int N, H, W;
int x[MAX_N], y[MAX_N];
int D[MAX_N][MAX_N];
bool vis[MAX_N] = {};


int dist(const int i, const int j){
    int dx = abs(x[i] - x[j]), dy = abs(y[i] - y[j]);
    return min(dx, W-dx) + min(dy, H-dy);
}

int Prim(int S){

    priority_queue<tiii, vector<tiii>, greater<tiii>> pq;

    vis[S] = true;
    for(int i=0; i<N; i++){
        if( vis[i] == true ) continue;
        pq.emplace( D[S][i], S, i );
    }

    int cost = 0;
    while( !pq.empty() ){
        int c, from, to;
        tie(c, from, to) = pq.top(); pq.pop();
        // printf("(%d, %d, %d)\n", c, from, to);
        if( vis[to] == true ) continue;
        vis[to] = true;
        cost += c;

        for(int i=0; i<N; i++){
            if( vis[i] == true ) continue;
            pq.emplace( D[to][i], to, i );
        }
    }

    return cost;
    
}

int main(void){
    cin >> N >> H >> W;
    for(int i=0; i<N; i++){
        cin >> x[i] >> y[i];
    }

    // init dist map
    for(int i=0; i<N; i++){
        for(int j=0; j<=i; j++){
            D[i][j] = D[j][i] = dist(i,j);
        }
    }

    fill(vis, vis+N, false);
    cout << Prim(0) << endl;
    return 0;
}