#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(void){
	int n, m;
	vector<int> head, knight;
	while( cin >> n >> m ){
		if( n == 0 && m == 0 ){
			break;
		}
		
		head.clear(); head.resize(n);
		knight.clear(); knight.resize(m);
		
		for(int i=0; i<n; i++){
			cin >> head[i];
		}
		for(int i=0; i<m; i++){
			cin >> knight[i];
		}
		
		std::sort(head.begin(), head.end());
		std::sort(knight.begin(), knight.end());
		
		int cost = 0;
		int i = 0, j = 0;
		while( i < n && j < m ){
			if( head[i] <= knight[j] ){
				cost += knight[j];
				i++;
			}
			j++;
		}
		
		if( i < n ){
			printf("Loowater is doomed!\n");
		}
		else{
			printf("%d\n", cost);
		}
	}
	return 0;
}