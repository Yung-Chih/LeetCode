#include <bits/stdc++.h>

using namespace std;

int N, M, S;
char MAP[100][100];


struct Rect{
    int color = -1;
    int row[2], col[2];

    Rect(int co = -1, int r1=1e9, int r2=-1e9, int c1 = 1e9, int c2 = -1e9 ){
        color = co;
        row[0] = r1;
        row[1] = r2;
        col[0] = c1;
        col[1] = c2;
    };
    Rect(const Rect& other){
        color = other.color;
        row[0] = other.row[0];
        row[1] = other.row[1];
        col[0] = other.col[0];
        col[1] = other.col[1];
    };
    int height(){
        return row[1] - row[0] + 1;
    };
    int width(){
        return col[1] - col[0] + 1;
    };
    int area(){
        return this->width() * this->height();
    }
};

Rect R[10];
int cnt[10] = {};
int psum[10][100][100] = {};
bool vis[10] = {};

void fill_map_rect(Rect R, char c){
    for(int i=R.row[0]; i<=R.row[1]; i++){
        for(int j=R.col[0]; j<=R.col[1]; j++){
            MAP[i][j] = c;
        }
    }
}

void print_map(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << MAP[i][j];
        }
        cout << endl;
    }
}


int num_equal(char c, int num){
    if( num == 0 ){
        return c == '.';
    }
    else{
        return c - '0' == num;
    }
};

void fill_psum(int num){
    psum[num][0][0] = num_equal(MAP[0][0], num);
    for(int i=1; i<N; i++){
        psum[num][i][0] = psum[num][i-1][0] + num_equal(MAP[i][0], num);
    }
    for(int j=1; j<N; j++){
        psum[num][0][j] = psum[num][0][j-1] + num_equal(MAP[0][j], num);
    }
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            psum[num][i][j] = psum[num][i-1][j] + psum[num][i][j-1] - psum[num][i-1][j-1] + num_equal(MAP[i][j], num);
        }
    }
}

int query_psum(int num, int r0, int c0, int r1, int c1){
    int A = psum[num][r1][c1];
    int B = (r0 > 0) ? psum[num][r0-1][c1] : 0;
    int C = (c0 > 0) ? psum[num][r1][c0-1] : 0;
    int D = (r0 > 0 && c0 > 0) ? psum[num][r0-1][c0-1] : 0;
    return A - B - C + D;
}


bool is_possible(int color, int r, int c){
    if( r+M > N || c+M > N) return false;
    int color_cnt = query_psum(color, r, c, r+M-1, c+M-1);
    // printf("color: %d, cnt: %d, (%d, %d)\n", color, color_cnt, r, c);
    if( color_cnt != cnt[color] ) return false;

    for(int i=0; i<=S; i++){
        if( i == color || vis[i] ) continue;
        // printf("  other: %d, cnt: %d, (%d, %d)\n", i, query_psum(i, r, c, r+M-1, c+M-1), r, c);
        if( query_psum(i, r, c, r+M-1, c+M-1) != 0 ) return false;
    }
    return true;
}

int main(void){
    cin >> N >> M >> S;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> MAP[i][j];
            if( isdigit(MAP[i][j]) ){
                int x = MAP[i][j] - '0';
                cnt[x]++;
                R[x].color = x;
                R[x].row[0] = min(R[x].row[0], i);
                R[x].row[1] = max(R[x].row[1], i);

                R[x].col[0] = min(R[x].col[0], j);
                R[x].col[1] = max(R[x].col[1], j);
            }
        }
    }

    memset(psum, 0, sizeof(psum));
    for(int i=0; i<=S; i++){
        fill_psum(i);
    }

    vector<Rect> ans;
    for(int i=1; i<=S; i++){
        R[i].color = i;
        // cout << R[i].color << ' ' << R[i].col[0] + 1 << ' ' << R[i].row[0] + 1 << endl;
        if( cnt[i] == M*M ){
            ans.push_back(R[i]);
            fill_map_rect(R[i], '?');
            vis[i] = true;
        }
    }

    for(int i=1; i<=S; i++){
        if( cnt[i] == 0 ){
            Rect r(ans.back());
            r.color = i;
            ans.push_back( r );
            vis[i] = true;
        }
    }
    // naive: O(S^2 N^2 * M^2), prefix sum: O( S N^2 ) + O( S^2 N^2 * S)
    // N, M <= 100, S <= 9
    for(int l=0; l<S && ans.size() < S; l++){
        for(int k=1; k<=S; k++){
            for(int i=0; i<=N-M && !vis[k]; i++){
                for(int j=0; j<=N-M && !vis[k]; j++){
                    if( is_possible(k, i, j) ){
                        Rect r(k, i, i+M-1, j, j+M-1);
                        ans.push_back(r);
                        vis[k] = true;
                        fill_map_rect(r, '?');
                        print_map();
                        cout << endl;
                    }
                }
            }
        }
    }
    // print_map();

    for(auto it=ans.rbegin(); it != ans.rend(); it++){
        cout << it->color << ' ' << it->col[0] + 1 << ' ' << it->row[0] + 1 << endl;
    }
    return 0;
}