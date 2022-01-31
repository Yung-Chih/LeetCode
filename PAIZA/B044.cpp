#include <bits/stdc++.h>

using namespace std;

int H, W;
int kill_cnt = 0, enemy_cnt = 0;
char MAP[100][100];
bool killed[100][100];

vector<int> boom[2][100], enemy[2][100];

bool can_kill(int ei, int ej, int bi, int bj){
    assert( ei == bi || ej == bj );
    int dist = abs(ei-bi) + abs(ej - bj);
    int range = MAP[bi][bj] - '0';
    if( dist > range ) return false;
    if( ei == bi ){
        for(int k = min(ej, bj); k <= max(ej, bj); k++){
            if( MAP[ei][k] == '#' ) return false;
        }
    }
    if( ej == bj ){
        for(int k = min(ei, bi); k <= max(ei, bi); k++){
            if( MAP[k][ej] == '#' ) return false;
        }
    }
    return true;
}

int main(void){
    cin >> H >> W;

    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            cin >> MAP[i][j];
            if( MAP[i][j] == 'X' ){
                enemy[0][i].emplace_back(j); // j-th pos of i-th row has enemy
                enemy[1][j].emplace_back(i); // i-th pos of j-th col has enemy
                enemy_cnt++;
            }
            if( '1' <= MAP[i][j] && MAP[i][j] <= '9' ){
                boom[0][i].emplace_back(j); // j-th pos of i-th row has enemy
                boom[1][j].emplace_back(i); // i-th pos of j-th col has enem
            }
        }
    }

    for(int i=0; i<100; i++){
        for(int ej : enemy[0][i]){
            if( killed[i][ej] == true ) continue;
            for(int bj : boom[0][i]){
                if( can_kill(i, ej, i, bj) == true ){
                    killed[i][ej] = true;
                    kill_cnt += 1;
                    break;
                }
            }
        }
    }

    for(int j=0; j<100; j++){
        for(int ei : enemy[1][j]){
            if( killed[ei][j] == true ) continue;
            for(int bi : boom[1][j]){
                if( can_kill(ei, j, bi, j) == true ){
                    killed[ei][j] = true;
                    kill_cnt += 1;
                    break;
                }
            }
        }
    }

    if( kill_cnt == enemy_cnt ){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    return 0;
}

/*
7 7
#######
#X.2..#
#.#.#.#
#.X.2.#
#.#1#.#
#4....#
#######
*/