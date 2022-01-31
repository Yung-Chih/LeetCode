#include <bits/stdc++.h>

using namespace std;

int G[6][6];
vector<int> ans;

void init_graph(){
    memset(G, 0, sizeof(int)*6*6);
}
void add_edge(int u, int v){
    G[u][v] = G[v][u] = 1;
}

void dfs(int u, int cnt){
    ans.emplace_back(u);
    if( cnt == 8 ){
        for(int i=0; i<ans.size(); i++) cout << ans[i];
        cout << endl;
    }
    else{
        for(int v=1; v<6; v++){
            if( G[u][v] == 0 ) continue;
            
            G[u][v] = G[v][u] = 0;
            dfs(v, cnt+1);
            G[u][v] = G[v][u] = 1;
        }
    }
    ans.pop_back();
    return;
}

int main(){
    init_graph();

    add_edge(1, 2);
    add_edge(1, 3);
    add_edge(1, 5);
    
    add_edge(2, 3);
    add_edge(2, 5);

    add_edge(3, 4);
    add_edge(3, 5);

    add_edge(4, 5);

    dfs(1, 0);
    return 0;
}