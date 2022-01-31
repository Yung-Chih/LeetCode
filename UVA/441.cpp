#include <bits/stdc++.h>

using namespace std;

void dfs(int s, int layer, const vector<int>& num){
    static vector<int> idx;
    if( layer == 0 ){
        cout << num[idx[0]];
        for(int i=1; i<idx.size(); i++)
            cout << ' ' << num[idx[i]];
        cout << endl;
    }
    else{
        for(int i=s; i<num.size(); i++){
            idx.emplace_back(i);
            dfs(i+1, layer-1, num);
            idx.pop_back();
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int k;
    vector<int> num;
    bool first = true;
    while(true){
        cin >> k;
        if( k == 0 ) break;

        num.clear();
        num.resize(k);
        for(int i=0; i<k; i++) cin >> num[i];

        std::sort(num.begin(), num.end());

        if( !first ) cout << '\n';
        dfs(0, 6, num);
        first = false;
        
    }
    return 0;
}