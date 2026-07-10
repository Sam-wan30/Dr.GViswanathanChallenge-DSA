class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> nodes;
        for (int i = 0; i < n; i++) {
            nodes.push_back({nums[i], i});
        }

        sort(nodes.begin(), nodes.end());

        // position of each original node in sorted order
        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[nodes[i].second] = i;
        }

        // farthest reachable index in one edge
        vector<int> farthest(n);
        int r = 0;
        for (int l = 0; l < n; l++) {
            r = max(r, l);
            while (r + 1 < n && nodes[r + 1].first - nodes[l].first <= maxDiff)
                r++;
            farthest[l] = r;
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> jump(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            jump[0][i] = farthest[i];

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                jump[k][i] = jump[k - 1][jump[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = q[0];
            int v = q[1];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int l = pos[u];
            int t = pos[v];

            if (l > t)
                swap(l, t);

            int cur = l;
            int dist = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (jump[k][cur] < t && jump[k][cur] > cur) {
                    cur = jump[k][cur];
                    dist += (1 << k);
                }
            }

            if (farthest[cur] >= t)
                ans.push_back(dist + 1);
            else
                ans.push_back(-1);
        }

        return ans;
    }
};