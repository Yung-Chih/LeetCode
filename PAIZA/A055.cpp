#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int H,W;
char MAP[100][100];
bool viz[100][100];
pii S;

bool valid(pii pos){
    if( pos.first < 0 || pos.first >= H ) return false;
    if( pos.second < 0 || pos.second >= W) return false;
    return true;
}
bool is_exit(pii pos){
    return ( pos.first == 0 || pos.second == 0 || pos.first == H-1 || pos.second == W-1);
}

int main(void){
    cin >> H >> W;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            cin >> MAP[i][j];
            viz[i][j] = false;
            if( MAP[i][j] == 'S' ){
                S = pii(i, j);
            }
        }
    }

    queue<pii> q;
    q.emplace(S);

    bool flag = false;
    while( !q.empty() ){
        pii pos = q.front(); q.pop();
        if( is_exit(pos) ){
            flag = true;
            break;
        }
        if( viz[pos.first][pos.second] ) continue;
        viz[pos.first][pos.second] = true;

        for(int i=-1; i<=1; i+=2){
            pii nei( pos.first + i, pos.second);
            if( !valid(nei) ) continue;
            if( viz[nei.first][nei.second] ) continue;
            if( MAP[nei.first][nei.second] == '#' ) continue;
            
            q.emplace(nei);
        }
        for(int i=-1; i<=1; i+=2){
            pii nei( pos.first, pos.second + i);
            if( !valid(nei) ) continue;
            if( viz[nei.first][nei.second] ) continue;
            if( MAP[nei.first][nei.second] == '#' ) continue;
            
            q.emplace(nei);
        }

    }


    if(flag){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }

    return 0;
}