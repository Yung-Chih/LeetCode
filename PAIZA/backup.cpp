#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
using tiii = tuple<int, int, int>;
using pii = pair<int, int>;
#define MAX_N (2 * (int)1e5 + 5)

const ll M = ((ll)1e9+7);

struct Frac{
    ll a, b;
    Frac(ll _a = 0, ll _b = 1){
        this->construct(_a, _b);
    }
    Frac(const Frac& other ){
        this->construct(other.a, other.b);
    }
    void construct(ll _a = 0, ll _b = 1){
        assert( _b != 0 );
        if( _a == 0 ){
            a = 0, b = 1;
        }
        else{
            // ll g = __gcd(_a, _b);
            a = _a % M , b = _b % M;
        }
    }

    Frac operator = (const Frac& other){
        this->a = other.a, this->b = other.b;
        return *this;
    }
    Frac operator + (const Frac& other ) const{
        return Frac( this->a * other.b + this->b * other.a, this->b * other.b);
    }
    Frac operator - (const Frac& other ) const{
        return Frac( this->a * other.b - this->b * other.a, this->b * other.b);
    }
    Frac operator * (const Frac& other ) const{
        return Frac( this->a * other.a, this->b * other.b);
    }
    Frac operator / (const Frac& other ) const{
        return Frac( this->a * other.b, this->b * other.a);
    }
};

ostream& operator << (ostream& os, const Frac& x){
    return os << x.a << "/" << x.b;
}


int N, Q;
vector<int> A, B;
vector<int> P;
vector<int> D;

void fill_depth(){
    vector<vector<int>> G;
    G.resize(N+1);
    for(int i=2; i<=N; i++){
        G[ P[i] ].emplace_back(i);
    }
    queue<pair<int, int>> q;
    q.emplace(1, 0);
    while( !q.empty() ){
        int x = q.front().first;
        int d = q.front().second;
        q.pop();
        if( D[x] != -1 ) continue;
        D[x] = d;

        for( int v : G[x] ){
            q.emplace(v, d+1);
        }
    }
}

void LCA_path(int u, int v, vector<int>& path_u, vector<int>& path_v){
    int du = D[u], dv = D[v];
    path_u.clear(), path_v.clear();

    path_u.emplace_back(u); path_v.emplace_back(v);
    while( du < dv ){
        v = P[v];
        dv--;
        path_v.emplace_back(v);
    }
    while( du > dv ){
        u = P[u];
        du--;
        path_u.emplace_back(u);
    }
    while( u != v ){
        u = P[u], v = P[v];
        du--, dv--;
        path_u.emplace_back(u);
        path_v.emplace_back(v);
    }
}

Frac occProb(int u){
    vector<int> path;
    while( u != 0 ){
        path.emplace_back(u);
        u = P[u];
    }
    Frac p = Frac(A[1], (ll)1e6);
    for(auto it = path.rbegin()+1; it != path.rend(); it++){
        int v = *it;
        p = p * Frac(A[v], (ll)1e6) + (Frac(1,1) - p) * Frac(B[v], (ll)1e6);
    }
    return p;
}
Frac condProb(const vector<int>& path, bool flag){
    Frac p = Frac(flag, 1);
    for(auto it = path.rbegin()+1; it != path.rend(); it++){
        int v = *it;
        p = p * Frac(A[v], (ll)1e6) + (Frac(1,1) - p) * Frac(B[v], (ll)1e6);
    }
    return p;
}

ll fpow(ll x, ll n, ll M){
    assert( n >= 0 && x != 0 );
    ll k = x, res = 1;
    while( n > 0 ){
        if( n & 1 ) res = (res * k)%M;

        k = (k*k) % M;
        n = n >> 1;
    }
    return res;
}

ll to_output(Frac x){
    // find z s.t. z * b = a mod (MOD)
    // z = b^{-1} * a mod (MOD)
    ll z = fpow(x.b, M-2, M) * x.a % M;
    return z;
}

void process(){
    A.clear(), B.clear(), P.clear();
    D.clear();

    cin >> N >> Q;
    A.resize(N+1), B.resize(N+1), P.resize(N+1);
    D.resize(N+1, -1);

    cin >> A[1]; B[1] = 0; P[1] = 0;
    for(int i=2; i<=N; i++){
        cin >> P[i] >> A[i] >> B[i];
    }

    fill_depth();


    int u, v, a;
    vector<int> path_u, path_v;
    for(int i=0; i<Q; i++){
        cin >> u >> v;
        LCA_path(u, v, path_u, path_v);
        a = path_u.back();
        /*
        cout << "LCA Path: " << endl;
        for(int x : path_u) cout << x << ' ';
        cout << endl;
        for(int x : path_v) cout << x << ' ';
        cout << endl;
        */
        Frac pa = occProb(a);
        Frac pua = condProb(path_u, true);
        Frac pva = condProb(path_v, true);

        Frac puna = condProb(path_u, false);
        Frac pvna = condProb(path_v, false);
        /*
        cout << "P[ " << a << " ] = " << pa << endl;
        cout << "P[ " << u << " | " << a << " ] = " << pua << endl;
        cout << "P[ " << v << " | " << a << " ] = " << pva << endl;

        cout << "P[ not " << a << " ] = " << (Frac(1,1) - pa) << endl;
        cout << "P[ " << u << " | not " << a << " ] = " << puna << endl;
        cout << "P[ " << v << " | not " << a << " ] = " << pvna << endl;

        cout << endl;
        */
        Frac Puv = pa * pua * pva + (Frac(1,1) - pa) * puna * pvna;
        // cerr << Puv << ": " << (double)Puv.a / (double) Puv.b << endl;

        ll z = to_output(Puv);
        cout << ' ' << z;
    }
    cout << endl;
}
int main(void){
    int T;
    cin >> T;

    for(int i=1; i<=T; i++){
        printf("Case #%d:", i);
        process();
    }
    return 0;
}