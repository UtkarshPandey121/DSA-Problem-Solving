class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        int m = order.size();
        int n = friends.size();
        vector<int>ans;
        
        for(int i=0; i<m; i++){
            int searching = order[i];
            for(int j=0; j<n; j++){
                if(order[i] == friends[j]) {
                    ans.push_back(searching);
                }
            }
        }
        return ans;
    }
};
