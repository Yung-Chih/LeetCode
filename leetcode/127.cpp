#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <tuple>
#include <iostream>
using namespace std;

class Solution {
private:
    int dist(const string& a, const string& b){
        int cnt = 0;
        for(int i=0; i<a.size(); i++){
            cnt += a[i] != b[i];
        }
        return cnt;
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue< tuple<int, int> > q;
        vector<int> D(wordList.size(), false);
        vector<bool> vis(wordList.size(), false);

        for(int i=0; i<wordList.size(); i++){
            int d = dist(endWord, wordList[i]);
            D[i] = d;
            if( dist(beginWord, wordList[i]) == 1 ){
                q.emplace(i, 1);
            }
        }
        


        while( !q.empty() ){
            int i, step;
            tie(i, step) = q.front();
            q.pop();
            if( vis[i] ) continue;
            vis[i] = true;
            if( D[i] == 0 ) return step+1;

            for(int j=0; j<wordList.size(); j++){
                if( vis[j] ) continue;
                if( dist(wordList[i], wordList[j]) == 1 ){
                    q.emplace(j, step+1);
                }
            }
        }
        return 0;
    }
};

int main(){

    Solution sol;
    vector<string> wordlist = {"ymann","yycrj","oecij","ymcnj","yzcrj","yycij","xecij","yecij","ymanj","yzcnj","ymain"};

    printf("%d\n", sol.ladderLength("ymain", "oecij", wordlist) );

}