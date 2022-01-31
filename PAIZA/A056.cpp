#include <bits/stdc++.h>

using namespace std;

char Board[51][51];
int N, Q;

int dist(int i, int j, int r, int c){
    return abs(i - r) + abs( j - c );
}

void place(int r, int c, int k, int color){
    Board[r][c] = (color == 1) ? 'B' : 'W';

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if( Board[i][j] == '.' ) continue;
            if( dist( i, j, r, c) > k ) continue;
            Board[i][j] = Board[r][c];
        }
    }
}

int main(void){
    cin >> N >> Q;
    memset(Board, '.', sizeof(Board));
    
    int color = 1;
    for(int i=0; i<Q; i++){
        int y, x, k;
        cin >> y >> x >> k;
        place(y, x, k, color);
        color ^= 1;
    }

    int cnt_W = 0, cnt_B = 0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cnt_W += Board[i][j] == 'W';
            cnt_B += Board[i][j] == 'B';
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout << Board[i][j];
        }
        cout << endl;
    }
    if( cnt_W < cnt_B ){
        cout << "B" << endl;
    }
    else if( cnt_W > cnt_B ){
        cout << "W" << endl;
    }
    else{
        cout << "D" << endl;
    }
    return 0;
}