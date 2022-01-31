#include <bits/stdc++.h>

using namespace std;

int dp[1001][2];

int dfs(int u, int pa, vector<set<int>>& Adj);

bool process();


int main(void){
	// ios::sync_with_stdio(false);
	// cin.tie(0);
	while(process());
	return 0;
}

bool process(){
	int N;
	cin >> N;
	if( N == 0 ) return false;


	vector<set<int>> Adj;
	Adj.resize(N);
	for(int i=0; i<N; i++){
		int deg;
		cin >> deg;
		for(int j=0; j<deg; j++){
			int x;
			cin >> x;
			Adj[i].emplace(x-1);
		}
	}

	if( N == 1 ){
		std::cout << 1 << std::endl;
	}
	else{
		memset(dp, 0, sizeof(int) * 1001 * 2 );
		std::cout << dfs(0, -1, Adj) << std::endl;
	}
	return true;
}

int dfs(int u, int pa, vector<set<int>>& Adj){
	dp[u][0] = 0;
	dp[u][1] = 1;
	for(int v : Adj[u]){
		if( v == pa ) continue;
		dfs(v, u, Adj);

		dp[u][0] += dp[v][1];
		dp[u][1] += min(dp[v][0], dp[v][1]);
	}
	return min(dp[u][0], dp[u][1]);
}
