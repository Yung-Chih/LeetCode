#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace std;

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

class Solution {
public:

    int largestRectangleArea(vector<int>& heights) {
        // left-right sweep line
        vector<int> H;
        H.insert(H.end(), heights.begin(), heights.end());
        H.emplace_back(0);
        int res = H[0];
        stack<pii> st;
        st.emplace(H[0], 0);
        for(int i=1; i<H.size(); i++){
            while( !st.empty() && st.top().first > H[i]){
                int h = st.top().first;
                cout << st.top().second << endl;
                st.pop();
                int idx = st.empty()? -1: st.top().second;
                printf("h, idx: %d %d\n", h, idx);
                printf("Area: (%d ~ %d) x %d = %d\n", idx, i-1, h, (i-idx-1) * h);
                res = max(res, (i-idx-1) * h);
            }
            st.emplace(H[i], i);
        }
        return res;
    }
};
int main(){
    vector<int> heights = {2,1,5,6,2,3};
    // vector<int> heights = {2,2,2,2};
    // vector<int> heights = {0,1,0,2,0,3,0};
    // vector<int> heights = {1,5,6,2,2,3,2};
    Solution sol;
    cout << sol.largestRectangleArea(heights) << endl;
    return 0;
}