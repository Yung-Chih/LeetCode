#include <bits/stdc++.h>

using namespace std;
#define MAX_SIZE 1000
#define WALL 1
#define GOAL 3

int M, N;
int sr, sc, gr, gc;
int MAP[MAX_SIZE][MAX_SIZE];
int D[MAX_SIZE][MAX_SIZE];
int dr[4] = {1, -1, 0,  0};
int dc[4] = {0,  0, 1, -1};

bool valid(int r, int c){
    return (0 <= r && r < N && 0 <= c && c <= M );
}

int main(void){
    cin >> M >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            char c;
            cin >> c;
            if( c == 's' ){
                MAP[i][j] = 2;
                sr = i, sc = j;
            }
            else if( c == 'g' ){
                MAP[i][j] = 3;
                gr = i, gc = j;
            }
            else{
                MAP[i][j] = c - '0';
            }
            D[i][j] = 1e9;
        }
    }
    cout << "MAP: " << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << MAP[i][j] << ' ';
        }
        cout << endl;
    }

    // memset(D, 1e9, sizeof(D));
    queue<tuple<int,int, int>> q;
    q.emplace(sr, sc, 0);

    while( !q.empty() ){
        int r, c, d;
        tie(r, c, d) = q.front(); q.pop();
        if( D[r][c] != 1e9 ) continue;
        D[r][c] = d;

        for(int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if( !valid(nr, nc) ) continue;
            if( MAP[nr][nc] == WALL ) continue;
            q.emplace(nr, nc, d+1);
        }
    }

    cout << "Dist: " << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if( D[i][j] == 1e9 ){
                cout << 'X' << ' ';
            }
            else{
                cout << D[i][j] << ' ';
            }
        }
        cout << endl;
    }
    if( D[gr][gc] != 1e9 ){
        cout << D[gr][gc] << endl;
    }
    else{
        cout << "Fail" << endl;
    }
    return 0;
}