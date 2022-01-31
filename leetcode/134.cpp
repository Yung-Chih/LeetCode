#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int N = gas.size();
        int i = 0, j = i, g;
        g = gas[i];
        while( i < N && j < i + N ){
            if( cost[j%N] <= g ){
                g -= cost[j%N];
                j++;
                g += gas[j%N];
            }
            else if( i == j ){
                j = ++i;
                if( i < N ) g = gas[i];
            }
            else{
                g -= gas[i] - cost[i];
                i++;
            }
        }
        return ( j == i+N ) ? i : -1;
    }
};

int main(){
    vector<int> gas = {4};
    vector<int> cost = {5};
    Solution sol;
    cout << sol.canCompleteCircuit(gas, cost) << endl;
}