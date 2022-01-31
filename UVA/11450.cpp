#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>

using namespace std;

void process();

int main(void){
	int T;
	cin >> T;
	while( T-- ){
		process();
	}
	return 0;
}

void process(){
	int M, C;
	cin >> M >> C;
	
	int gar[20][20];
	
	int K[20];
	for(int i=0; i<C; i++){
		cin >> K[i];
		for(int j=0; j<K[i]; j++)
			cin >> gar[i][j];
	}
	
	set<int> cost[20];
	
	for(int i=0; i<C; i++){
		for(int j=0; j<K[i]; j++){
			if( i == 0 ){
				cost[i].emplace( gar[i][j] );
			}
			else{
				for(int c : cost[i-1] ){
					int val = gar[i][j] + c;
					if( val > M ) continue;
					cost[i].emplace( gar[i][j] + c );
				}
			}
		}
	}
	
	if( cost[C-1].size() > 0 ){
		cout << (*cost[C-1].rbegin()) << endl;
	}
	else{
		cout << "no solution" << endl;
	}
}