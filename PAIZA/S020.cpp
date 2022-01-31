#include <bits/stdc++.h>

using namespace std;
#define MAX_SIZE 100
int N, M;
int W[MAX_SIZE], A[MAX_SIZE], C[MAX_SIZE];

struct Car
{
    int cap;
    int cost;
    Car(int ca=0, int co=1e9): cap(ca), cost(co){};
};


int main(void){
    cin >> N;
    for(int i=0; i<N; i++)
        cin >> W[i];

    cin >> M;
    for(int i=0; i<M; i++)
        cin >> A[i] >> C[i];

    vector<Car> Cars, next_Cars;
    for(int i=0; i<M; i++){
        if( W[0] > A[i] ) continue;
        Cars.emplace_back( A[i] - W[0], C[i] );
    }

    for(int i=1; i<N; i++){
        int nc = 1e9;
        for(Car car : Cars){
            if( W[i] > car.cap ){
                nc = min(nc, car.cost);
            }
            else{
                next_Cars.emplace_back(car.cap - W[i], car.cost);   
            }
        }

        for(int j=0; j<M; j++){
            if( W[i] > A[j] ) continue;
            next_Cars.emplace_back( A[j] - W[i], nc + C[j] );
        }

        std::swap(Cars, next_Cars);
        next_Cars.clear();
    }
    
    int ans = 1e9;
    for(Car car : Cars){
        ans = min(ans, car.cost);
    }
    cout << ans << endl;
    return 0;
}