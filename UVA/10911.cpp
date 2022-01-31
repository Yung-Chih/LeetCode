#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
using namespace std;

int N;
double x[20], y[20];
double dist[20][20];
double dp[1<<16];

double bit_dp(int mask){
	if( dp[mask] > -1 ) return dp[mask];
	if( mask == 0 ){
		return 0;
	}
	
	double res = 1e9;
	for(int i=0; i<2*N; i++){
		if( ((1<<i) & mask) == 0 ) continue;
		for( int j=i+1; j < 2*N; j++ ){
			if( ((1<<j) & mask) == 0 ) continue;
			int new_mask = mask ^ (1<<i) ^ (1<<j);
			res = min(res, bit_dp( new_mask ) + dist[i][j] );
			
		}
	}
	return dp[mask] = res;
}

int main(void){

	int cid = 0;
	while( scanf("%d", &N) ){
		if( N == 0 ) break;
		
		for(int i=0; i<2*N; i++){
			scanf("%*s %lf %lf", &x[i], &y[i]);
		}
		
		for(int i=0; i<2*N; i++){
			for(int j=0; j<2*N; j++){
				dist[i][j] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
				dist[i][j] = sqrt(dist[i][j]);
			}
		}
		
		fill( dp, dp + (1<<16), -1 );
		
		
		printf("Case %d: %.2lf\n", ++cid, bit_dp( (1<<(2*N)) - 1 ));
	}
	
	return 0;
}


