#include<bits/stdc++.h>

using namespace std;

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
    int P;
    cin >> P; getchar();
    vector<vector<int>> G;
    vector<int> cnt;
    G.resize(P+1);
    cnt.resize(P+1, -1);
    for(int i=1; i<=P; i++){
        string s;
        getline(cin, s);
        stringstream ss;
        ss << s;

        int x;
        while( ss >> x ){
            G[i].emplace_back(x);
        }
        cnt[i] = G[i].size();
    }

    int min_val = *min_element(cnt.begin()+1, cnt.end());

    bool first = true;
    for(int i=1; i<=P; i++){
        if( cnt[i] != min_val ) continue;
        if( !first ) cout << ' ';
        cout << i;
        first = false;
    }
    cout << endl;
}