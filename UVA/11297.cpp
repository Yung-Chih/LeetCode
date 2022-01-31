#include<bits/stdc++.h>

using namespace std;

int N, Q;
vector< vector<int> > Reg;

struct Node{
    int min_val = 1e9, max_val = -1e9;
    Node(const int& v=0): min_val(v), max_val(v) {};
};

class SegTree{
private:
    int maxR = 0;
    vector<Node> tree;
    Node query_res;
public:
    SegTree(){};

    void init(vector<int>& A){
        int N = A.size();
        maxR = N;
        tree.resize(N*4);
        build_tree(0, 0, maxR, A);
    }
    
    void build_tree(int idx, int L, int R, vector<int>& A){
        if( L + 1 == R ){
            tree[idx].min_val = tree[idx].max_val = A[L];
        }
        else{
            int mid = (L+R)/2;
            int lid = idx * 2 + 1, rid = idx * 2 + 2;
            build_tree(lid, L, mid, A);
            build_tree(rid, mid, R, A);
            tree[idx] = merge( tree[lid], tree[rid] );
        }
        // printf("[%d, %d): %d, %d\n", L, R, tree[idx].max_val, tree[idx].min_val);
    }

    Node merge(const Node& a, const Node& b) const{
        Node n;
        n.min_val = min(a.min_val, b.min_val);
        n.max_val = max(a.max_val, b.max_val);
        return n;
    }

    Node query(int l, int r){
        query_res.min_val = 1e9;
        query_res.max_val = -1e9;
        query(0, l, r, 0, maxR);
        return query_res;
    }
    void query(int idx, int l, int r, int L, int R){
        if( l <= L && R <= r){
            query_res.min_val = min(tree[idx].min_val, query_res.min_val);
            query_res.max_val = max(tree[idx].max_val, query_res.max_val);
            return;
        }
        int mid = (L+R)/2;
        int lid = idx*2+1, rid = idx*2+2;
        if( r <= mid ){
            query(lid, l, r, L, mid);
            return;
        }
        if( l >= mid ){
            query(rid, l, r, mid, R);
            return;
        }
        query(lid, l, mid, L, mid);
        query(rid, mid, r, mid, R);
    }

    void modify(int x, int y, int val){
        modify(0, x, y, val, 0, maxR);
    }
    void modify(int idx, int l, int r, int val, int L, int R){
        if( l <= L && R <= r){
            tree[idx].min_val = tree[idx].max_val = val;
            return;
        }
        int mid = (L+R)/2;
        int lid = idx*2+1, rid = idx*2+2;
        if( r <= mid ){
            modify(lid, l, r, val, L, mid);
        }
        else if( l >= mid ){
            modify(rid, l, r, val, mid, R);
        }
        else{
            modify(lid, l, mid, val, L, mid);
            modify(rid, mid, r, val, mid, R);
        }
        tree[idx] = merge( tree[lid], tree[rid] );
    }
};


int main(void){
    vector<SegTree> ST;

    scanf("%d", &N);
    Reg.resize(N);
    ST.resize(N);
    for(int i=0; i<N; i++){
        Reg[i].resize(N);
        for(int j=0; j<N; j++){
            scanf("%d", &Reg[i][j]);
        }
        ST[i].init(Reg[i]);

    }


    char op;
    int x[2], y[2], v;
    scanf("%d", &Q);
    for(int i=0; i<Q; i++){
        scanf(" %c", &op);
        if( op == 'q' ){
            scanf("%d %d %d %d", &x[0], &y[0], &x[1], &y[1]);
            x[0]--, y[0]--, x[1]--, y[1]--;
            Node res;
            res.min_val = 1e9;
            res.max_val = -1e9;
            for(int i=x[0]; i<=x[1]; i++){
                Node n = ST[i].query(y[0], y[1]+1);
                // printf("  %d %d\n", n.max_val, n.min_val);
                res.min_val = min(res.min_val, n.min_val);
                res.max_val = max(res.max_val, n.max_val);
            }
            printf("%d %d\n", res.max_val, res.min_val);
        }
        else{
            scanf("%d %d %d", &x[0], &y[0], &v);
            x[0]--, y[0]--;
            ST[ x[0] ].modify(y[0], y[0]+1, v);
        }
        
    }
    return 0;
}


/*

5
1 2 3 4 5
0 9 2 1 3
0 2 3 4 1
0 1 2 4 5
8 5 3 1 4
4
q 1 1 2 3
c 2 3 10

q 1 1 5 5
q 1 2 2 2
*/