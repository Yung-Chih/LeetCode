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
    int N;
    cin >> N;

    DisjointSet DS(N*N+1);

    for(int i=1; i<=N; i++){
        int k;
        cin >> k;
        for(int j=0; j<k; j++){
            int x;
            cin >> x;

            //printf("Uni (%d, %d), (%d, %d)\n", i+N, x, x+N, i);

            DS.Uni(i, x+N); // union i with x' ( Uni(enemy of x, i) )
            DS.Uni(x, i+N); // union x with i' ( Uni(enemy of i, x) )

        }
    }

    vector<int> cnt;
    cnt.resize(2*N+1, 0);

    for(int i=1; i<=N; i++){
        int pa = DS.top(i);
        cnt[pa]++;
    }

    int ans = 0;
    vector<bool> used(2*N+1, false);
    for(int i=1; i<=N; i++){
        if( DS.same(i, i+N) ) continue;
        int pa = DS.top(i), epa = DS.top(i+N);
        if( used[pa] || used[epa] ) continue;

        ans += max(cnt[pa], cnt[epa]);

        used[pa] = used[epa] = true;
    }

    std::cout << ans << '\n';

}

/*

3

5
1 3
1 1
0
1 5
0

8
2 4 5
2 1 3
0
0
0
1 3
0
1 5

3
2 2 3
1 3
1 1

*/