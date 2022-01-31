#include <bits/stdc++.h>

using namespace std;

bool process();

int lid(int x){ return 2*x+1; }
int rid(int x){ return 2*x+2; }

struct Node{
    int left, right, most;
    int left_cnt, right_cnt, most_cnt;

    void print(){
        printf("(%d, %d, %d), (%d, %d, %d)\n", left, right, most, left_cnt, right_cnt, most_cnt);
    }
};

void build_seg_tree(int idx, int L, int R, const vector<int>& A, vector<Node>& tree );
Node merge(const Node& a, const Node& b);
Node query(int idx, int l, int r, int L, int R, vector<Node>& tree);
int main(void){
    while(process());
    return 0;
}

bool process(){
    int N, Q;
    cin >> N;
    if( N == 0 ) return false;
    cin >> Q;

    vector<int> A(N);
    vector<Node> tree;
    for(int i=0; i<N; i++) cin >> A[i];

    tree.resize(4*N+4);
    build_seg_tree(0, 0, N, A, tree);

    for(int i=0; i<Q; i++){
        int l, r;
        cin >> l >> r; // 1-index, close interval [l, r]

        l--; // to 0-index, open interval [l, r)
        Node n = query(0, l, r, 0, N, tree);
        // n.print();

        std::cout << n.most_cnt << std::endl;
    }

    return true;
}

void build_seg_tree(int idx, int L, int R, const vector<int>& A, vector<Node>& tree ){
    if( R - L == 1 ){
        tree[idx].left = tree[idx].right = tree[idx].most = A[L];
        tree[idx].left_cnt = tree[idx].right_cnt = tree[idx].most_cnt = 1;
    }
    else{
        int mid = (L+R) / 2;
        build_seg_tree(lid(idx), L, mid, A, tree);
        build_seg_tree(rid(idx), mid, R, A, tree);
        tree[idx] = merge( tree[lid(idx)], tree[rid(idx)] );
    }
    
    // printf("[%d, %d): ", L, R);
    // tree[idx].print();
}

Node merge(const Node& a, const Node& b){
    Node res;
    res.left = a.left;
    res.left_cnt = a.left_cnt;

    res.right = b.right;
    res.right_cnt = b.right_cnt;

    if( a.right == b.left ){
        int mid = a.right, mid_cnt = a.right_cnt + b.left_cnt;
        int cnt[3] = {a.most_cnt, mid_cnt, b.most_cnt};
        int max_id = max_element(cnt, cnt+3) - cnt;
        if( max_id == 0 ){
            res.most = a.most;
            res.most_cnt = a.most_cnt;
        }
        else if( max_id == 1 ){
            res.most = mid;
            res.most_cnt = mid_cnt;
        }
        else if( max_id == 2 ){
            res.most = b.most;
            res.most_cnt = b.most_cnt;
        }

        if( a.left == mid ){
            res.left_cnt = mid_cnt;
        }
        if( mid == b.right ){
            res.right_cnt = mid_cnt;
        }
    }
    else{
        if( a.most_cnt >= b.most_cnt ){
            res.most = a.most;
            res.most_cnt = a.most_cnt;
        }
        else{
            res.most = b.most;
            res.most_cnt = b.most_cnt;
        }

    }
    return res;
}

Node query(int idx, int l, int r, int L, int R, vector<Node>& tree){
    int mid = (L+R) / 2;
    if( l == L && r == R ){
        return tree[idx];
    }
    if( r <= mid ){
        return query(lid(idx), l, r, L, mid, tree);
    }
    else if( l >= mid ){
        return query(rid(idx), l, r, mid, R, tree);
    }
    else{
        return merge(query(lid(idx), l, mid, L, mid, tree),
                     query(rid(idx), mid, r, mid, R, tree));
    }
}
/*
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0

A...K + KK..Z  or A...K + L...Z
left, right, max = (A, K, X) + (K, Z, Y) or (L, Z, Y)
It's sorted --> only the # of mid part will change!!
if right = left, max = max(K+K, X, Y)
otherwise, max = max(X,Y)

*/
