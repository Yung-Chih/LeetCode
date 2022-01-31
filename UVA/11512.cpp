#include <bits/stdc++.h>

using namespace std;

void process();
vector<int> build_suffix_array(const string& S);
string get_suffix(const string& S, const int idx ){
    return S.substr(idx, S.size()-idx);
}

struct Node{
    Node* parent;
    int cnt = 0;
    int len = 0;
    int best_path = -1;
    vector<int> l, r, sz;
    vector<Node*> child;
};


int main(void){
    int T;
    cin >> T;
    while(T--){
        process();
    }
    return 0;
}

void process(){
    std::string S;
    cin >> S;
    S += "$";

    vector<int> SA = build_suffix_array(S);
    vector<int> rank(SA.size()), LCP(SA.size());
    for(int i=0; i<SA.size(); i++){
        rank[ SA[i] ] = i;
    }


    // LCP = the common prefix length btw S[ SA[i] ...], S[ SA[i-1] ...]
    int k = 0;
    for(int i=0; i<S.size(); i++){
        if( rank[i] == 0 ){
            // if the rank of S[i ... ] = 0
            // S[i ...] is the smallest suffix
            // undefined for LCP[i]
            continue;
        }
        int j = SA[rank[i]-1]; // idx of suffix;
        while( S[i+k] == S[j+k] ) k++; // finite process because '$'
        LCP[ rank[i] ] = k;
        if( k > 0 ) k--;
    }
    /*
    std::cout << "Rank: " << endl;
    for(int i=0; i<SA.size(); i++){
        std::cout << rank[i] << ", " << get_suffix(S, i) << std::endl;
    }
    std::cout << "Suffix, LCP" << endl;
    for(int i=0; i<SA.size(); i++){
        std::cout << SA[i] << ", " << LCP[i] << ", " << get_suffix(S, SA[i]) << std::endl;
    }
    */
    int max_len = 0, max_idx = 0, cnt = 0;
    for(int i=1; i<SA.size(); i++){
        if( LCP[i] == 0 ) continue;

        if( LCP[i] > max_len ){
            max_len = LCP[i];
            max_idx = SA[i];
            cnt = 2;
        }
        else if( LCP[i] == LCP[i-1] && LCP[i] == max_len ){
            cnt++;
        }
    }

    if( max_len == 0 ){
        std::cout << "No repetitions found!" << std::endl;
    }
    else{
        std::cout << S.substr(max_idx, max_len) << ' ' << cnt << endl;
    }
}

struct MyCMP{
    vector<int> rank;
    int len;
    bool operator() (int i, int j){
        if( rank[i] != rank[j] ){
            return rank[i] < rank[j];
        }
        // int a = (i+len < rank.size()) ? rank[i+len] : -1;
        // int b = (j+len < rank.size()) ? rank[j+len] : -1;
        int a = rank[(i+len)%rank.size()]; // for S[0...n-1] + '$'
        int b = rank[(j+len)%rank.size()];
        return a < b;
    }
};

vector<int> build_suffix_array(const string& S){
    vector<int> SA(S.size()), rank(S.size()), new_rank(S.size());

    for(int i=0; i<S.size();i++) SA[i] = i;
    for(int i=0; i<S.size(); i++) rank[i] = S[i];

    for(int n=1; n<S.size(); n = n << 1 ){
        MyCMP less_cmp;
        less_cmp.rank = rank;
        less_cmp.len = n;

        std::sort(SA.begin(), SA.end(), less_cmp);

        int r = 0;
        new_rank[ SA[0] ] = r;
        for(int i=1; i<S.size(); i++){
            if( less_cmp(SA[i-1], SA[i]) ) r++;
            new_rank[ SA[i] ] = r;
        }
        swap(rank, new_rank);

        if( r == S.size()-1 ) break;
    }
    return SA;
}
