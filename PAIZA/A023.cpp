#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> sche;
vector<int> F;

int main(void){
    cin >> N;
    sche.resize(N, 0);
    for(int i=0; i<N; i++){
        cin >> sche[i];
        sche[i] ^= 1;
        if( sche[i] == 1 ) F.emplace_back(i);
    }
    for(int i=0; i<N; i++){
        cout << sche[i];
    }
    cout << endl;

    int ans = 0, cur = sche[0] + sche[1] + sche[2] + sche[3] + sche[4] + sche[5];
    bool flag = false;
    int cnt = 0;
    for(int i=0; i<sche.size()-6; i++){
        cur -= ( i < 1 ) ? 0 : sche[i-1];
        cur += sche[i+6];
        cout << cur << endl;
        if( cur >= 2 ){
            if( flag == false ){
                flag = true;
                cnt = 7;
            }
            else cnt++;
        }
        else{
            flag = false;
            cnt = 0;
        }
        ans = max(ans, cnt);
    }
    /*
    const int INTERVAL = 7;
    int i = 0, j = 0, k = 1;
    int ans = 0;

    while( i < F.size() && j < F.size() && k < F.size() ){
        while( i+1 < F.size() && F[i+1] - F[i] >= INTERVAL ){ // search the first 0 pair in 7 days
            i++;
        }
        if( i == F.size() - 1 ) break;
        j = i, k = i+1;
        while( k+1 < F.size() && F[k+1] - F[j] <= INTERVAL && F[k] - F[j] < INTERVAL){
            j = k++;
        }

        int lcnt = min(7 - (F[i+1] - F[i] + 1), F[i]); // left append
        int rcnt = min(7 - (F[k] - F[k-1] + 1), N-F[k]-1); // right append

        ans = max(ans, F[k] - F[i] + 1 + max(lcnt, rcnt) );

        // update interval
        i = k;
    }
    */
    cout << ans << endl;
    
    return 0;
}