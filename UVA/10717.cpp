#include <bits/stdc++.h>

using namespace std;

int lcm_2(int a, int b){
    return a / __gcd(a,b) * b;
}

int lcm_4(int a, int b, int c, int d){
    int lcm_ab = lcm_2(a ,b);
    int lcm_cd = lcm_2(c, d);
    return lcm_2(lcm_ab, lcm_cd);
}

pair<int, int> solve(int a, int b, int c, int d, int table){
    int g = lcm_4(a, b, c, d);
    int r = table % g;
    int lb = table - r, rb = ( r > 0 ) ? table + g - r : table;
    return pair<int, int>(lb, rb);
}

pair<int, int> solve(vector<int>& coin, int table){
    pair<int, int> ans(0, INT_MAX);
    for(int i=0; i<coin.size(); i++){
        for(int j=i+1; j<coin.size(); j++){
            for(int k=j+1; k<coin.size(); k++){
                for(int l=k+1; l<coin.size(); l++){
                    pair<int, int> res = solve( coin[i], coin[j], coin[k], coin[l], table);
                    ans.first = max(ans.first, res.first);
                    ans.second = min(ans.second, res.second);
                }
            }
        }
    }
    return ans;
}

bool process();

int main(int argc, char* argv[] ){
    while(process());
    return 0;
}

bool process(){
    int n, t;
    cin >> n >> t;
    if( n == 0 && t == 0 ) return false;

    vector<int> coin(n), table(t);

    for(int i=0; i<n; i++){
        cin >> coin[i];
    }
    for(int i=0; i<t; i++){
        cin >> table[i];
    }

    for(int i=0; i<t; i++){
        pair<int, int> ans = solve(coin, table[i]);
        std::cout << ans.first << ' ' << ans.second << '\n';
    }
    return true;
}