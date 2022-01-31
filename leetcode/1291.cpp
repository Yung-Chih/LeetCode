#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        int ld = 0, rd = 0;
        for(long long int k=1; k<=low; k*=10) ld++;
        for(long long int k=1; k<=high; k*=10) rd++;
        vector<int> res;
        for(int d = ld; d <= rd; d++){

            int x = 1, k;
            int shift = 1;
            for(k=2; k<=d; k++){
                x = x*10 + k;
                shift = 10*shift + 1;
            }
            if( low <= x && x <= high)
                res.emplace_back(x);
            for(;k<10; k++){
                x += shift;
                if( low <= x && x <= high )
                    res.emplace_back(x);
            }
        }
        return res;
    }
};

int main(){
    int low, high;
    cin >> low >> high;
    Solution sol;
    vector<int> A = sol.sequentialDigits(low, high);
    for(int i=0; i<A.size(); i++){
        cout << A[i] << " \n"[i == A.size()-1];
    }
    return 0;
}