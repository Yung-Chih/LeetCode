#include<bits/stdc++.h>

using namespace std;

string S;

int main(void){
    int T;
    cin >> T;
    getline(cin, S);
    for(int cnt=0; cnt < T; cnt++){
        vector< pair<int, string> > x;
        for(int i=0; i<3; i++){
            string S;
            getline(cin, S);
            stringstream ss;
            ss << S;
            if( i == 0 ) continue;
            else if( i == 1 ){
                int p;
                while( ss >> p ){
                    x.emplace_back(p, "");
                }
            }
            else if( i == 2 ){
                for(int k=0; k<x.size(); k++){
                    ss >> x[k].second;
                }
            }
        }

        sort(x.begin(), x.end());

        if( cnt ) cout << endl;
        for(pair<int, string>& p : x){
            std::cout << p.second << endl;
        }
    }
    return 0;
}

/*
1

3 1 2
32.0 54.7 -2
*/