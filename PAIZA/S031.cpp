#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct pipe{
    ll b, p;
};

struct cmp_1{
    bool operator()(const pipe &a, const pipe& b){
        return a.p < b.p || (a.p == b.p && a.b > b.b);
    }
};
struct cmp_2{
    bool operator()(const pipe &a, const pipe& b){
        return a.b > b.b || (a.b == b.b && a.p < b.p);
    }
}
;
ll N, C, K;
vector<pipe> P;

int main(void){
    cin >> N >> C >> K;
    P.resize(N);
    for(int i=0; i<N; i++){
        cin >> P[i].b >> P[i].p;
    }

    cmp_1 c1;
    cmp_2 c2;
    sort(P.begin(), P.end(), c1);
    assert(N >= K);


    priority_queue<pipe, vector<pipe>, cmp_2> pq; // pop from small neck, large cost

    ll cost = 0;
    for(int i=0; i<K; i++){ // insert from small cost, large neck
        cost += P[i].p;
        pq.emplace(P[i]);
    }

    pipe top = pq.top();
    for(int i=K; i<N; i++){
        if( cost - top.p + P[i].p > C ) continue;
        if( top.b < P[i].b ){
            cost = cost - top.p + P[i].p;

            pq.pop();
            pq.emplace(P[i]);
            top = pq.top();
        }
    }

    cout << top.b << endl;
    return 0;
}

/*
5 10 3
2 4
2 2
2 2
2 3
2 4
*/