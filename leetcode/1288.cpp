    #include <bits/stdc++.h>
    using namespace std;

    struct MyCmp{
        bool operator()(const vector<int>& A, const vector<int>& B){
            return pair<int,int>(A[0], -A[1]) < pair<int,int>(B[0], -B[1]);
        }
    };

    class Solution {
    public:
        void print(int l, int r, vector< vector<int> > intervals){
            for(int i=l; i<r; i++){
                cout << intervals[i][0] << ' ' << intervals[i][1] << endl;
            }
        }
        bool covered(vector<int>& A, vector<int>& B){
            return A[0] <= B[0] && B[1] <= A[1];
        }
        int removeCoveredIntervals(vector<vector<int>>& intervals) {
            MyCmp cmp;
            sort(intervals.begin(), intervals.end(), cmp);
            int i = 0, j = 0;
            int cnt = 0;
            while( i < intervals.size() ){
                j = i;
                while( j < intervals.size() && covered(intervals[i], intervals[j]) ) j++;
                print(i, j, intervals);
                cout << "------" << endl;
                cnt++;
                i = j;
            }
            return cnt;
        }
    };

int main(){
    vector< vector<int>> intervals = {{1,4},{3,6},{2,8}, {2,5}, {1,2}, {1, 5}, {3,9}};
    Solution sol;
    cout << sol.removeCoveredIntervals(intervals) << endl;
    return 0;
}