#include <string>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Solution {
private:
    vector<int> next, prev;
    void init(const int& N){
        next.resize(N+1);
        prev.resize(N+1);

        next[N] = 0;
        for(int i=0; i<N; i++){
            next[i] = i+1;
        }
        prev[0] = N;
        for(int i=1; i<=N; i++){
            prev[i] = i-1;
        }
    }

    void del(int i){
        int p = prev[i], n = next[i];
        next[p] = n;
        prev[n] = p;
        next[i] = prev[i] = -1;
    }

    string to_string(const string& num){
        int N = num.size();
        string res;
        for(int i = next[N]; i != N; i = next[i] ){
            res += num[i];
        }
        return res;
    }

    bool is_peak(int i, const string& num){
        int N = num.size();
        if( i == num.size() ) return false;
        if( prev[i] == N && next[i] == N ){
            return true;
        }
        int p = ( prev[i] == N ) ? num[i] : num[prev[i]];
        int n = ( next[i] == N ) ? num[i] : num[next[i]];
        if( p > num[i] || n > num[i] ) return false;
        return (p < num[i]) || (n < num[i]);
    }

    void remove_head(const string& num){
        int N = num.size();
        for(int i = next[N]; num[i] == '0'; i = next[N] ){
            del(i);
        }
    }
public:
    string removeKdigits(string num, int k) {
        int N = num.size();
        this->init(N);

        int it = 0;
        int i;
        for(i=0; i<k; i++){
            int s = it;
            while( !is_peak(it, num) ){
                it = next[it];
                if( it == s ) break;
            }
            if( it == s && !is_peak(it, num) ) break;
            int p = prev[it];
            del(it);
            it = p;
            remove_head(num);
            // cout << to_string(num) << endl;
        }
        for(; i<k && next[N] != N; i++){
            del(next[N]);
        }
        string res = to_string(num);
        return (res.size()) ? res : "0";
    }
};

int main(){
    Solution sol;
    // string num = "1234";
    // string num = "1432219";
    string num = "14321678";
    // string num = "102002";
    for(int k=0; k<=num.size(); k++){
        cout << "k = " << k << ": " << sol.removeKdigits(num, k) << endl;
    }
    // cout << "k = " << 0 << ": " << sol.removeKdigits(num, 0) << endl;
    // cout << "k = " << 2 << ": " << sol.removeKdigits(num, 2) << endl;
    return 0;
}

/// 145229
/// 14522 or 15229 or 14229
/*
    1 3 5 -> kill 5
    1 3 2 -> kill 3
    5 3 1 -> kill 5
    5 3 4 -> kill 5
    4 3 5 -> kill 4
*/