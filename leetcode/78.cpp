class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int N = nums.size();
        vector<vector<int>> pset(1<<N);
        
        for(int i=0; i<pset.size(); i++){
            for(int k=0; k<N; k++){
                if( i & (1<<k) ){
                    pset[i].emplace_back( nums[k] );
                }
            }
        }
        return pset;
    }
};
