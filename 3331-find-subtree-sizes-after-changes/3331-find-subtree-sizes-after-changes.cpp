class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);

        function<void(int)> dfs = [&](int node) {
            int ch = s[node] - 'a';

            if (last[ch] != -1) {
                newParent[node] = last[ch];
            }

            int prev = last[ch];
            last[ch] = node;

            for (int child : adj[node]) {
                dfs(child);
            }

            last[ch] = prev;
        };

        dfs(0);

        vector<vector<int>> newAdj(n);

        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        function<void(int)> dfs2 = [&](int node) {
            for (int child : newAdj[node]) {
                dfs2(child);
                ans[node] += ans[child];
            }
        };

        dfs2(0);

        return ans;
    }
};