#include <bits/stdc++.h>

using namespace std;
#define MAX_N 100
#define BLACK -1

vector<int> G[MAX_N+1];
vector<int> ans;
int color[MAX_N+1];
int n, k;

void draw(int u, int c){
    color[u] = c;
    for(int v : G[u]){
        color[v] += ( c == BLACK ) ? 1 : 0;
    }
}
void undraw(int u, int c){
    color[u] = 0;
    for(int v : G[u]){
        color[v] -= ( c == BLACK ) ? 1 : 0;
    }
}

void search(int s){
    // the best solution when s = black
    // black = -1, white = postive int, un-colored = 0

    static vector<int> black_list;
    draw(s, BLACK);
    black_list.emplace_back(s);

    bool has_child = false;
    for(int i=1; i<=n; i++){
        if( color[i] != 0 ) continue;
        search(i); // sub-solution when i = black (s = black, neighbor of s = white)
        has_child = true;
    }

    if( has_child == false && ans.size() < black_list.size() ){ // coloring finish && the solution better than current solution.
        ans.clear();
        ans.insert(ans.end(), black_list.begin(), black_list.end());
    }

    undraw(s, BLACK);
    black_list.pop_back();
}

void process();

int main(){
    int T;
    cin >> T;
    while(T--){
        process();
    }
    return 0;
}

void process(){
    for(int i=0; i<=MAX_N; i++) G[i].clear();
    ans.clear();
    fill( color, color + MAX_N + 1, 0 );

    cin >> n >> k;
    
    for(int i=0; i<k; i++){
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    for(int i=1; i<=n; i++){
        search(i);
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    cout << ans[0];
    for(int i=1; i<ans.size(); i++){
        cout << ' ' << ans[i];
    }
    cout << endl;
}

