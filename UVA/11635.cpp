#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <tuple>
#include <queue>

using namespace std;
using tiii = tuple<int,int,int>;
using pii = pair<int,int>;

bool process();

vector<int> SSSP( int S, int N, vector<vector<pii>> Edge );

int main(void){
	// ios::sync_with_stdio(false);
	// cin.tie(0);
	while(process());
	return 0;
}

bool process(){
	int N, M, H;
	vector<int> hid;
	vector< vector< pii > > Edge;
	cin >> N;
	if( N == 0 ) return false;
	
	cin >> H;
	hid.resize(H);
	for(int i=0; i<H; i++){
		cin >> hid[i];
		hid[i]--;
	}
	sort(hid.begin(), hid.end());
	
	cin >> M;
	Edge.resize(N);
	for(int i=0; i<M; i++){
		int a, b, t;
		cin >> a >> b >> t;
		a--, b--;
		Edge[a].emplace_back(b, t);
		Edge[b].emplace_back(a, t);
	}
	
	
	if( hid.empty() || hid.front() != 0 ){
		hid.insert(hid.begin(), 0);
	}
	if( hid.empty() || hid.back() != N-1 ){
		hid.emplace_back(N-1);
	}
	
	vector<vector<int>> HD;
	HD.resize(hid.size());
	for( int i=0; i<hid.size(); i++) HD[i].resize(hid.size(), -1);
	// std::cout << "HD Size: " << HD.size() << endl;
	
	for( int i=0; i<hid.size(); i++ ){
		int src = hid[i];
		vector<int> d = SSSP(src, N, Edge);
		/*
		for(int x : d ){
			cout << x << ' ';
		}
		cout << endl;
		*/
		for( int j=0; j<hid.size(); j++){
			if( i != j ){
				HD[i][j] = ( d[ hid[j] ] <= 600 ? 1 : 1e9);
			}
			if( i == j ){
				HD[i][j] = 0;
			}
		}

	}
	/*
	for(int i=0; i<hid.size(); i++){
		cout << hid[i] << ": ";
		for(int j=0; j<hid.size(); j++){
			cout << HD[i][j] << ' ';
		}
		cout << endl;
	}
	*/
	
	for(int k=0; k<hid.size(); k++){
		for(int i=0; i<hid.size(); i++){
			for(int j=0; j<hid.size(); j++){
				if( HD[i][j] > HD[i][k] + HD[k][j] ){
					HD[i][j] = HD[i][k] + HD[k][j];
				}
			}
		}

	}
	/*
	for(int i=0; i<hid.size(); i++){
		cout << hid[i] << ": ";
		for(int j=0; j<hid.size(); j++){
			cout << HD[i][j] << ' ';
		}
		cout << endl;
	}
	*/
	

	
	/*
	for(int i=0; i<N; i++){
		vector<int> d = SSSP(i, N, Edge);
		for(int x : d){
			cout << x << ' ' ;
		}
		cout << endl;
	}
	*/
	
	int ans = ( HD[0][ HD.size() - 1] != 1e9 ) ? HD[0][ HD.size() - 1] - 1 : -1;
	std::cout << ans << '\n';
	return true;
}

vector<int> SSSP( int S, int N, vector<vector<pii>> Edge ){
	vector<int> dist(N, 1e9);
	dist[S] = 0;
	
	for( auto p : Edge[S] ){
		int dest = p.first, t = p.second;
	}
	
	priority_queue< pii > pq;
	pq.emplace(0, S);
	
	while( !pq.empty() ){
		int t, u;
		auto p = pq.top();
		t = p.first, u = p.second;
		
		pq.pop();

		
		for( auto p : Edge[u] ){
			int v = p.first, w = p.second;
			int new_dist = dist[u] + w;
			if( new_dist < dist[v] && new_dist <= 600){
				dist[v] = new_dist;
				pq.emplace( dist[v], v);
			}
			// if dist[v] is greater than 600 --> cut the path
		}
		
	}
	
	return dist;
}
