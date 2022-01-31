#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
string S;
ull ptr = 0;
ull cnt[26];

void parse(ull base){
    char c = S[ptr];
    if( isdigit(c) ){
        ull val = 0;
        while( ptr < S.size() && isdigit(S[ptr]) ){
            val = val * 10 + (S[ptr] - '0');
            ptr++;
        }
        parse(base * val);
    }
    else if( 'a' <= c && c <= 'z' ){
        cnt[ c - 'a' ] += base;
        ptr++;
    }
    else if( c == '(' ){
        ptr++;
        while( S[ptr] != ')' ){
            parse(base);
        }
        ptr++;
    }
}

int main(void){
    cin >> S;
    memset(cnt, 0, sizeof(cnt));

    while( ptr < S.size() ){
        parse(1);
    }
    for(int i=0; i<26; i++){
        cout << (char)('a'+i) << ' ' << cnt[i] << endl;
    }
    return 0;
}