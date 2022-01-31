#include <bits/stdc++.h>

using namespace std;

struct DisjointSet{
private:
    vector<int> fa;
public:
    DisjointSet(int _n = 0){
        this->init(_n);
    }
    void init(int _n){
        fa.resize(_n);
        for(int i=0; i<_n; i++){
            fa[i] = i;
        }
    }

    void Uni(int x, int y){
        assert( 0 <= x && x < fa.size());
        if( this->same(x,y) ) return;
        int px = top(x), py = top(y);
        fa[px] = py;
    }
    int top(int x){
        assert( 0 <= x && x < fa.size());
        if( fa[x] == x ) return x;
        return fa[x] = top( fa[x] );
    }
    bool same(int x, int y){
        assert( 0 <= x && x < fa.size());
        return top(x) == top(y);
    }
};

bool process();


int main(void){
    while(process());
    return 0;
}

bool process(){
    static bool first_case = true;
    int m;
    if( !(cin >> m) ){
        return false;
    }

    vector<int> DNA[2];
    DNA[0].resize(m), DNA[1].resize(m);
    for(int i=0; i<m; i++){
        string s;
        cin >> s;
        if( isalpha(s[0]) ){
            DNA[0][i] = s[0] - 'A' + 201;
        }
        else{
            stringstream ss;
            ss << s;
            ss >> DNA[0][i];
        }
    }
    for(int i=0; i<m; i++){
        string s;
        cin >> s;
        if( isalpha(s[0]) ){
            DNA[1][i] = s[0] - 'A' + 201;
        }
        else{
            stringstream ss;
            ss << s;
            ss >> DNA[1][i];
        }
    }

    DisjointSet my_set(201+4);

    for(int i=0; i<m; i++){
        // cout << DNA[0][i] << ' ' << DNA[1][i] << endl;
        if( my_set.same(DNA[0][i], DNA[1][i]) ) continue;
        my_set.Uni(DNA[0][i], DNA[1][i]);
    }

    bool has_sol = true;
    vector<char> ans;
    ans.resize(201, '-');

    for(int k=201; k<=204; k++){
        for(int i=0; i<=200; i++){
            if( my_set.same(k, i) ){
                if( ans[i] == '-' ) ans[i] = k-201+'A';
                else has_sol = false;
            }
        }
    }

    if( !first_case )
        cout << endl;
    if( has_sol ){
        cout << "YES" << endl;
        for(int i=0; i<=200; i++){
            if( ans[i] != '-' ) cout << i << ' ' << ans[i] << endl;
        }
    }
    else{
        cout << "NO" << endl;
    }

    first_case = false;
    return true;
}

/*
7
A
1
2
B
1
D
4
1
3
B
2
3
D
4
*/