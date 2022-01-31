#include<bits/stdc++.h>
using namespace std;

map<char, int> op_id;
int op_next[4][4] = {
        {0, 1, 2, 3},
        {1, 1, 2, 2},
        {2, 1, 2, 1},
        {3, 1, 2, 0}
    };
void init(){
    op_id['X'] = 0;
    op_id['F'] = 1;
    op_id['E'] = 2;
    op_id['I'] = 3;
}

struct Node{
    int cnt[2] = {0, 0};
    bool dirty = false;
    int op = 0;

    void take_op(){
        assert(dirty == true);
        // cout << "Take op: " << op << endl;
        switch (op)
        {
        case 1: // 'F': set to 1
            cnt[1] = cnt[1] + cnt[0];
            cnt[0] = 0;
            break;
        case 2: // 'E': set to 0
            cnt[0] = cnt[1] + cnt[0];
            cnt[1] = 0;
            break;
        case 3: // 'I': inverse
            swap(cnt[0], cnt[1]);
            break;
        default:
            break;
        }
    }
};

class SegTree{
private:
    int left_id(const int& root){ return root * 2 + 1; };
    int right_id(const int& root){ return root * 2 + 2; };
public:
    std::vector<int> ref;
    vector<Node> T;

    SegTree(){};
    void build_tree(){
        T.resize(ref.size()*4);
        build_tree(0, 0, ref.size());
    }
    Node query(int l, int r){
        return query(0, l, r, 0, ref.size());
    }
    
    void modify(int l, int r, int op){
        return modify(0, l, r, op, 0, ref.size());
    }

    string cur_str(){
        string s;
        for(int i=0; i<ref.size(); i++){
            s += query(i, i+1).cnt[1] + '0';
        }
        return s;
    }

private:
    void build_tree(int idx, int L, int R){
        assert( 0 <= idx && idx < T.size() );
        if( L + 1 == R ){
            T[idx].cnt[ ref[L] ] = 1;
            T[idx].cnt[ ref[L]^1 ] = 0;
            T[idx].dirty = false;
            T[idx].op = 0;
            return;
        }
        int mid = (L+R) / 2;
        int lid = left_id(idx), rid = right_id(idx);

        build_tree(lid, L, mid);
        build_tree(rid, mid, R);

        T[idx] = pull(T[lid], T[rid]);
    }

    Node pull(const Node& a, const Node& b){
        assert( !a.dirty && !b.dirty );
        assert( a.op == 0 && b.op == 0 );
        Node n;
        n.cnt[0] = a.cnt[0] + b.cnt[0];
        n.cnt[1] = a.cnt[1] + b.cnt[1];
        n.dirty = false;
        n.op = 0;
        return n;
    }

    void push(const int& idx){
        assert( T[idx].dirty );
        // push op to children
        if( T[idx].cnt[0] + T[idx].cnt[1] > 1 ){
            int lid = left_id(idx), rid = right_id(idx);
            T[lid].dirty = T[rid].dirty = true;
            T[lid].op = op_next[ T[lid].op ][ T[idx].op ];
            T[rid].op = op_next[ T[rid].op ][ T[idx].op ];
        }

        // update root
        T[idx].take_op();
        T[idx].dirty = false;
        T[idx].op = 0;
    }

    Node query(int idx, int l, int r, int L, int R){
        assert( 0 <= idx && idx < T.size() );
        
        if( T[idx].dirty ) push(idx);

        if( l == L && R == r ) return T[idx];

        int mid = (L+R) / 2;
        int lid = left_id(idx), rid = right_id(idx);
        if( L <= l && r <= mid ){ // left side
            return query(lid, l, r, L, mid);
        }
        else if( mid <= l && r <= R ){ // right side
            return query(rid, l, r, mid, R);
        }
        else if( L <= l && r <= R ){ // both side
            return pull( query(lid, l, mid, L, mid), query(rid, mid, r, mid, R) );
        }
        else{ // out of range
            std::cout << "query: out of range" << endl;
            assert(false);
            return Node();
        }
    }

    void modify(int idx, int l, int r, int op, int L, int R){
        assert( 0 <= idx && idx < T.size() );

        // push dirty flag to children
        if( T[idx].dirty ) push(idx);

        int mid = (L+R) / 2;
        int lid = left_id(idx), rid = right_id(idx);

        if( l == L && R == r ){ // set dirty flag and operation
            assert(!T[idx].dirty && T[idx].op == 0);
            T[idx].op = op;
            T[idx].dirty = true;
            return;
        }
        if( L <= l && r <= mid ){ // left side
            modify(lid, l, r, op, L, mid);
        }
        else if( mid <= l && r <= R ){ // right side
            modify(rid, l, r, op, mid, R);
        }
        else if( L <= l && r <= R ){ // both side
            modify(lid, l, mid, op, L, mid);
            modify(rid, mid, r, op, mid, R);
        }
        else{ // out of range
            std::cout << "modify: out of range" << endl;
            assert(false);
        }
        // ensure children have correct value
        if( T[lid].dirty ) push(lid);
        if( T[rid].dirty ) push(rid);

        // update cur node
        T[idx] = pull( T[lid], T[rid] );

    }

};

void process(int c);

int main(void){
    init();
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        process(i);
    }
    return 0;
}

void process(int c){
    int N;
    cin >> N;
    SegTree ST;
    for(int i=0; i<N; i++){
        int k;
        vector<int> s;
        cin >> k;
        char c = getchar();
        while( ( c = getchar() ) != '\n' ){
            s.emplace_back( c - '0' );
        }
        while( k-- ){
            ST.ref.insert(ST.ref.end(), s.begin(), s.end());
        }
    }


    ST.build_tree();

    int Q;
    cin >> Q;
    int s_cnt = 0;
    printf("Case %d:\n", c+1);
    for(int i=0; i<Q; i++){
        char c_op;
        int l, r;
        cin >> c_op >> l >> r;
        

        if( c_op == 'S' ){ // query
            Node n = ST.query(l, r+1);

            printf("Q%d: %d\n", ++s_cnt, n.cnt[1]);
            // printf("%s\n", ST.cur_str().c_str() );
            // cout << "Q" << ++s_cnt << ": " << n.cnt[0] << ' ' << n.cnt[1] << '\n';
        }
        else{ // modify
            // printf("op: %c, op_id: %d\n", c_op, op_id[c_op]);
            ST.modify(l, r+1, op_id[c_op] );
        }
    }
}

/*
1\2| X | F | E | I |
 X | X | F | E | I |
 F | F | F | E | E |
 E | E | F | E | F |
 I | I | F | E | X |

2
2
5
10
2
1000
5
F 0 17
I 0 5
S 1 10
E 4 9
S 2 10
3
3
1
4
0
2
0
2
I 0 2
S 0 8


1
1
1
01010011
100
S 0 7
S 0 3
S 1 6
S 0 5
I 0 7
S 0 7
S 0 3
S 1 6
S 0 5
I 0 7
I 1 3
I 1 7
S 0 7
S 0 3
S 1 6
S 0 5
S 4 7
F 0 2
S 5 6
S 2 4
S 3 7
E 3 5
*/