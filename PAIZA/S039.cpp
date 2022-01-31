#include <bits/stdc++.h>

using namespace std;

int H, W;
char MAP[500][500];
struct Rect{
    int row_l, row_r;
    int col_l, col_r;
    Rect(int rl = 0, int rr = 0, int cl = 0, int cr = 0): row_l(rl), row_r(rr), col_l(cl), col_r(cr){};
    int Area(){
        return (row_r - row_l + 1) * (col_r - col_l + 1);
    }
};
bool operator< (const Rect r1, const Rect r2){
    return tie(r1.row_l, r1.row_r, r1.col_l, r1.col_r) < tie(r2.row_l, r2.row_r, r2.col_l, r2.col_r);
};

vector<Rect> rects;

vector<Rect> get_row_rect(int row){
    vector<Rect> res;
    int l = 0, r = 0;
    while( l < W && r < W ){
        while( l < W && MAP[row][l] == '#' ) l++;
        if( l == W ) break;
        r = l+1;
        while( r < W && MAP[row][r] == '.' ) r++;
        res.emplace_back(row, row, l, r-1);
        l = r;
    }
    return res;
}

bool can_merge( Rect r1, Rect r2 ){
    if( abs(r1.row_r - r2.row_l) == 1 ){
        return (r1.col_l <= r2.col_l && r2.col_l <= r1.col_r) || ( r2.col_l <= r1.col_l && r1.col_l <= r2.col_r);
    }
    return false;
}
Rect merge(Rect r1, Rect r2){
    Rect res;
    res.row_l = min(r1.row_l, r2.row_l);
    res.row_r = max(r1.row_r, r2.row_r);
    int arr[4] = {r1.col_l, r1.col_r, r2.col_l, r2.col_r};
    sort(arr, arr+4);
    res.col_l = arr[1];
    res.col_r = arr[2];
    return res;
}

int main(void){
    cin >> H >> W;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            cin >> MAP[i][j];
        }
    }

    rects = get_row_rect(0);
    int L = 0, R = rects.size();

    for(int row=1; row < H; row++){
        // cout << "row: " << row << endl;
        vector<Rect> next = get_row_rect(row);
        // cout << next.size() << endl;
        vector<Rect> merged;
        for(int i=L; i<R; i++){
            for(int j=0; j<next.size(); j++){
                if( can_merge(rects[i], next[j]) ){
                    merged.emplace_back( merge(rects[i], next[j]) );
                }
            }
        }

        L = R;
        rects.insert(rects.end(), next.begin(), next.end());
        rects.insert(rects.end(), merged.begin(), merged.end());
        R = rects.size();
    }

    Rect ans;
    for(Rect r : rects){
        // cout << r.row_l << ' ' << r.row_r << ' ' << r.col_l << ' ' << r.col_r << ": " << r.Area() << endl;
        if( ans.Area() < r.Area() ){
            ans = r;
        }
    }
    cout << ans.Area() << endl;
    // cout << ans.row_l << ' ' << ans.row_r << ' ' << ans.col_l << ' ' << ans.col_r << endl;
    return 0;
}