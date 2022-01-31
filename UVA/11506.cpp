#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <tuple>
#include <queue>
#include <bits/stdc++.h>

using namespace std;
using tiii = tuple<int,int,int>;
using pii = pair<int,int>;

template<typename T>
struct DINIC{
	static const int MAXN=105;
	static const T INF=INT_MAX;
	int n, level[MAXN], cur[MAXN];
	struct edge{
		int v,pre;
		T cap,flow,r;
		edge(int v,int pre,T cap):v(v),pre(pre),cap(cap),flow(0),r(cap){}
	};
	int g[MAXN];
	vector<edge> e;
	void init(int _n){
		memset(g,-1,sizeof(int)*((n=_n)+1));
		e.clear();
	}
	void add_edge(int u,int v,T cap,bool directed=false){
		e.push_back(edge(v,g[u],cap));
		g[u]=e.size()-1;
		e.push_back(edge(u,g[v],directed?0:cap));
		g[v]=e.size()-1;
	}
	int bfs(int s,int t){
		memset(level,0,sizeof(int)*(n+1));
		memcpy(cur,g,sizeof(int)*(n+1));
		queue<int> q;
		q.push(s);
		level[s]=1;
		while(q.size()){
			int u=q.front();q.pop();
			for(int i=g[u];~i;i=e[i].pre){
				if(!level[e[i].v]&&e[i].r){
					level[e[i].v]=level[u]+1;
					q.push(e[i].v);
					if(e[i].v==t)return 1;
				}
			}
		}
		return 0;
	}
	T dfs(int u,int t,T cur_flow=INF){
		if(u==t)return cur_flow;
		T df;
		for(int &i=cur[u];~i;i=e[i].pre){
			if(level[e[i].v]==level[u]+1&&e[i].r){
				if(df=dfs(e[i].v,t,min(cur_flow,e[i].r))){
					e[i].flow+=df;
					e[i^1].flow-=df;
					e[i].r-=df;
					e[i^1].r+=df;
					return df;
				}
			}
		}
		return level[u]=0;
	}
	T dinic(int s,int t,bool clean=true){
		if(clean){
			for(size_t i=0;i<e.size();++i){
				e[i].flow=0;
				e[i].r=e[i].cap;
			}
		}
		T ans=0, mf=0;
		while(bfs(s,t))while(mf=dfs(s,t))ans+=mf;
		return ans;
	}
};
bool process();


int main(void){
	// ios::sync_with_stdio(false);
	// cin.tie(0);
	while(process());
	return 0;
}

bool process(){
	int M, W;
	cin >> M >> W;
	
	if( M == 0 && W == 0 ) return false;
	vector<vector<pii>> G; // (dest, weight)
	G.resize(M*2);
	
	DINIC<int> solver;
	solver.init(M*2);
	
	// (u --> u'), in to u, out from u'
	// G[0].emplace_back( M, 1e9+9 ); 
	solver.add_edge(0, M, 1e9+9, true);
	for(int i=0; i<M-2; i++){
		int x, w;
		cin >> x >> w;
		x--;
		
		// G[x].emplace_back( x + M, w);
		solver.add_edge(x, x+M, w, true);
	}
	// G[M-1].emplace_back( 2*M - 1, 1e9+9 ); // (dest, weight)
	solver.add_edge(M-1, 2*M-1, 1e9+9, true);
	
	for(int i=0; i<W; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		
		// u <---> v : --> u -> u' ----> v -> v' ---
		// G[u+M].emplace_back(v, w);
		// G[v+M].emplace_back(u, w);
		
		solver.add_edge(u+M, v, w, true);
		solver.add_edge(v+M, u, w, true);
	}
	
	// max flow, min cut algorithm
	std::cout << solver.dinic(0, 2*M-1) << '\n';
	return true;
}

