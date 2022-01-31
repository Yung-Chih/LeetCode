#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
using tiii = tuple<int, int, int>;
using pii = pair<int, int>;
#define MAX_N (2 * (int)1e5 + 1)

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

struct Node{
    int depth = -1;
    vector<int> Par;

    Frac occProb;
    vector<Frac> TProb;
    vector<Frac> FProb;

    ~Node(){
        Par.clear();
        TProb.clear();
        FProb.clear();
    }
    void preprocess(vector<Node>& Tree );
};


int N, Q;
vector<Node> Tree;

void Tree_Process();
int LCA(int u, int v);
Frac condProb(int u, int v, int flag);

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
    return ( z >= 0 ) ? z : z + M;
}


void process(){
    cin >> N >> Q;

    Tree.clear();
    Tree.resize(N+1);

    int a, b, p;
    cin >> a;

    Tree[1].occProb = Frac(a, 1e6);
    for(int i=2; i<=N; i++){
        int p;
        cin >> p >> a >> b;
        Tree[i].Par.emplace_back(p);
        Tree[i].TProb.emplace_back(a, 1e6);
        Tree[i].FProb.emplace_back(b, 1e6);
    }

    Tree_Process();

    vector<int> path_u, path_v;
    for(int i=0; i<Q; i++){
        int u, v, anc;
        cin >> u >> v;

        anc = LCA(u, v);
        
        /*
        LCA_path(u, v, path_u, path_v);
        a = path_u.back();
        
        std::cout << "LCA Path: " << endl;
        for(int x : path_u)
            std::cout << D[x] << ' ' << x << endl;
        std::cout << endl;
        for(int x : path_v)
            std::cout << D[x] << ' ' << x << endl;
        std::cout << endl;
        */
        
        Frac pa = Tree[anc].occProb;
        Frac pua = condProb(u, anc, 1);
        Frac pva = condProb(v, anc, 1);

        Frac puna = condProb(u, anc, 0);
        Frac pvna = condProb(v, anc, 0);
        
        /*
        std::cout << "P[ " << a << " ] = " << pa << endl;
        std::cout << "P[ " << u << " | " << a << " ] = " << pua << endl;
        std::cout << "P[ " << v << " | " << a << " ] = " << pva << endl;

        std::cout << "P[ not " << a << " ] = " << (Frac(1,1) - pa) << endl;
        std::cout << "P[ " << u << " | not " << a << " ] = " << puna << endl;
        std::cout << "P[ " << v << " | not " << a << " ] = " << pvna << endl;
        std::cout << endl;
        */
        
        
        Frac Puv = pa * pua * pva + (Frac(1,1) - pa) * puna * pvna;
        // cerr << Puv << ": " << (double)Puv.a / (double) Puv.b << endl;

        ll z = to_output(Puv);
        std::cout << ' ' << z;
        
    }
    std::cout << endl;
}
int main(void){
    int T;
    cin >> T;

    for(int i=1; i<=T; i++){
        printf("Case #%d:", i);
        process();
        // cerr << endl;
    }
    return 0;
}

void Tree_Process(){
    vector< vector<int> > G;
    G.resize(N+1);

    for(int i=2; i<=N; i++){
        int par = Tree[i].Par[0];
        G[par].emplace_back(i);
    }

    queue<int> q;

    Tree[1].depth = 0;

    for( int u : G[1] ){
        q.emplace(u);
    }

    while( !q.empty() ){
        int u = q.front();
        q.pop();

        Tree[u].preprocess( Tree );

        for(int v : G[u]){
            q.emplace(v);
        }
    }
    
}

void Node::preprocess(vector<Node>& Tree){
    int pa = this->Par[0];
    this->occProb = this->TProb[0] * Tree[pa].occProb + this->FProb[0] * ( Frac(1, 1) - Tree[pa].occProb );
    this->depth = Tree[pa].depth + 1;

    int i = 1;
    while( ( depth >> i ) > 0 ){
        // P[i] = 2^i-th ancestor = [ 2^(i-1) ] + [ 2^(i-1) ]
        Node& anc = Tree[this->Par[i-1]];
        this->Par.emplace_back( anc.Par[i-1] );

        Frac tp = TProb[i-1] * anc.TProb[i-1] + FProb[i-1] * ( Frac(1, 1) - anc.TProb[i-1] );
        Frac fp = TProb[i-1] * anc.FProb[i-1] + FProb[i-1] * ( Frac(1, 1) - anc.FProb[i-1] );
        this->TProb.emplace_back(tp);
        this->FProb.emplace_back(fp);

        i++;
    }
}

int LCA(int u, int v){
    if( Tree[u].depth < Tree[v].depth )
        swap(u, v);

    int d = Tree[u].depth - Tree[v].depth, k = 0;
    while( Tree[u].depth > Tree[v].depth ){ // make the depth of u, v the same
        if( (1 << k) & d ) {
            u = Tree[u].Par[k];
        }
        k++;
    }

    while( u != v ){ // LCA btw 2^(i-1), 2^i, 
        int i = 0;
        while( i < Tree[u].Par.size() && Tree[u].Par[i] != Tree[v].Par[i] ) i++;
        u = Tree[u].Par[ max(i-1, 0) ];
        v = Tree[v].Par[ max(i-1, 0) ];
    }
    return u;
}

Frac condProb(int u, int v, int flag){
    int d = Tree[u].depth - Tree[v].depth, k = 0;
    vector<int> step, path;

    path.emplace_back(u);
    while( Tree[u].depth > Tree[v].depth ){
        if( (1 << k) & d ) {
            u = Tree[u].Par[k];
            step.emplace_back(k);
            path.emplace_back(u);
        }
        k++;
    }

    assert( path.back() == v );

    Frac prob = Frac(flag, 1);
    for(int i = step.size()-1; i>=0; i--){
        int x = path[i], k = step[i];

        prob = Tree[x].TProb[k] * prob + Tree[x].FProb[k] * ( Frac(1, 1) - prob );
    }

    return prob;
}