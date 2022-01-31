#include <bits/stdc++.h>

using namespace std;

using tiii = tuple<int, int, int>;
using pii = pair<int, int>;
string A, B, S;
int dp[1001][1001];

int main(void){
    cin >> A;
    cin >> B;
    cin >> S;

    A = '-' + A;
    B = '-' + B;

    memset(dp, 0, sizeof(dp));

    for(int i=1; i<A.size(); i++){
        int u = dp[i-1][0];
        dp[i][0] = max( dp[i][0], dp[i-1][0] + ( A[i] == S[u] ) );
    }
    for(int j=1; j<B.size(); j++){
        int l = dp[0][j-1];
        dp[0][j] = max( dp[0][j], dp[0][j-1] + ( B[j] == S[l] ) );
    }
    for(int i=1; i<A.size(); i++){
        for(int j=1; j<B.size(); j++){
            // dp[i][j] = max fit len with C by (A[:i], B[:j])
            int u = dp[i-1][j];
            int l = dp[i][j-1];
            // int ul = dp[i-1][j-1];
            // dp[i][j] = -1;
            dp[i][j] = max( dp[i][j], dp[i-1][j] + ( A[i] == S[u] ) );
            dp[i][j] = max( dp[i][j], dp[i][j-1] + ( B[j] == S[l] ) );
            // dp[i][j] = max( dp[i][j], dp[i-1][j-1] + ( A[i] == S[ul] && B[j] == S[ul] ) );
            
        }
    }

    int cost = 1e9;
    for(int i=0; i<A.size(); i++){
        for(int j=0; j<B.size(); j++){
            // cout << dp[i][j] << ' ';
            if( dp[i][j] == S.size() ){
                cost = min(cost, i+j);
            }
        }
        // cout << endl;
    }
    cout << cost << endl;
    return 0;
}

/*
ab
bac
abc
*/