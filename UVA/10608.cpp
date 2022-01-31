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

void process();

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--){
        process();
    }
    return 0;
}

void process(){
    int N, M;
    cin >> N >> M;

    DisjointSet DS(N+1);

    for(int i=0; i<M; i++){
        int u, v;
        cin >> u >> v;
        DS.Uni(u, v);
    }

    vector<int> cnt(N+1, 0);
    for(int i=1; i<=N; i++){
        cnt[ DS.top(i) ]++;
    }
    std::cout << (*max_element(cnt.begin(), cnt.end())) << '\n';

}

/*

2
3 2
1 2
2 3
10 12
1 2
3 1
3 4
5 4
3 5
4 6
5 2
2 1
7 1
1 2
9 10
8 9

*/