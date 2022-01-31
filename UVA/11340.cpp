#include<bits/stdc++.h>

using namespace std;
void process();

int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
        process();
    }
}

void process(){
    int K;
    scanf("%d", &K);
    getchar(); // eat the '\n';

    map<char, int> cent;
    for(int i=0; i<K; i++){
        char c;
        int x;
        scanf("%c %d", &c, &x);
        cent.emplace(c, x);
        getchar(); // eat the '\n';
    }

    int L;
    scanf("%d", &L); getchar();

    unsigned long long money = 0;
    int line_cnt = 0;
    while( line_cnt < L ){
        char c = getchar();
        switch (c)
        {
        case '\n':
            line_cnt++;
            break;
        default:
            if( cent.count(c) ){
                money += cent[c];
            }
            break;
        }
    }

    printf("%llu.%02llu$\n", money/100, money%100);
}

/*
2
7
a 3
W 10
A 100
, 10
k 7
. 3
I 13
7
ACM International Collegiate Programming Contest (abbreviated
as ACM-ICPC or just ICPC) is an annual multi-tiered competition
among the universities of the world. The ICPC challenges students
to set ever higher standards of excellence for themselves
through competition that rewards team work, problem analysis,
and rapid software development.
From Wikipedia.
7
a 3
W 10
A 100
, 10
k 7
. 3
I 13
7
ACM International Collegiate Programming Contest (abbreviated
as ACM-ICPC or just ICPC) is an annual multi-tiered competition
among the universities of the world. The ICPC challenges students
to set ever higher standards of excellence for themselves
through competition that rewards team work, problem analysis,
and rapid software development.
From WikipediaAAA.
*/