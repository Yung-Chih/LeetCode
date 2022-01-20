#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int i = 0, j = 0, k = 0;
        while( i < flowerbed.size() ){
            while( i < flowerbed.size() && flowerbed[i] == 1 ) i++;
            j = i;
            while( j < flowerbed.size() && flowerbed[j] == 0 ) j++;
            // [i, j) = 0,0,...,0
            k = j-i-2;
            if( i == 0 ) k++;
            if( j == flowerbed.size() ) k++;
            n -=(k+1)/2;
            if( n <= 0 ) return true;
            i = j;
        }
        return n <= 0;
    }
};


int main(){
    int n = 2;

    Solution sol;
    vector<int> flowerbed = {1,0,0,0,1};
    cout << sol.canPlaceFlowers(flowerbed, 1) << endl;
    cout << sol.canPlaceFlowers(flowerbed, 2) << endl;
    
    vector<int> flowerbed2 = {0,0,0,0,1};
    cout << sol.canPlaceFlowers(flowerbed2, 1) << endl;
    cout << sol.canPlaceFlowers(flowerbed2, 2) << endl;
    cout << sol.canPlaceFlowers(flowerbed2, 3) << endl;
    vector<int> flowerbed3 = {0,0,0,0,0};
    cout << sol.canPlaceFlowers(flowerbed3, 1) << endl;
    cout << sol.canPlaceFlowers(flowerbed3, 2) << endl;
    cout << sol.canPlaceFlowers(flowerbed3, 3) << endl;
    cout << sol.canPlaceFlowers(flowerbed3, 4) << endl;
}