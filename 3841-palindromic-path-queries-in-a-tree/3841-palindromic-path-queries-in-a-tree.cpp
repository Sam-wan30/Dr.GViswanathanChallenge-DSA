class Solution {
public:
    vector<int> seg, parent, depth, heavy, head, pos, sz;
    int timer = 0;

    void updateSeg(int idx, int l, int r, int p, int val) {
        if (l == r) {
            seg[idx] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (p <= mid)
            updateSeg(idx * 2, l, mid, p, val);
        else
            updateSeg(idx * 2 + 1, mid + 1, r, p, val);

        seg[idx] = seg[idx * 2] ^ seg[idx * 2 + 1];
    }

    int querySeg(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) / 2;

        return querySeg(idx * 2, l, mid, ql, qr) ^
               querySeg(idx * 2 + 1, mid + 1, r, ql, qr);
    }

    int queryPath(int u, int v, int n) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            mask ^= querySeg(
                1, 0, n - 1,
                pos[head[u]], pos[u]
            );

            u = parent[head[u]];
        }

        if (depth[u] > depth[v])
            swap(u, v);

        mask ^= querySeg(1, 0, n - 1, pos[u], pos[v]);

        return mask;
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        sz.assign(n, 1);
        seg.assign(4 * n, 0);

        timer = 0;

        // Iterative DFS to avoid stack overflow
        vector<int> order;
        order.reserve(n);
        order.push_back(0);

        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];

            for (int v : adj[u]) {
                if (v == parent[u])
                    continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }

        // Calculate subtree sizes and heavy children
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            int maxSize = 0;

            for (int v : adj[u]) {
                if (v == parent[u])
                    continue;

                sz[u] += sz[v];

                if (sz[v] > maxSize) {
                    maxSize = sz[v];
                    heavy[u] = v;
                }
            }
        }

        // Heavy-Light Decomposition
        for (int u : order) {
            if (parent[u] != -1 && heavy[parent[u]] == u)
                continue;

            for (int v = u; v != -1; v = heavy[v]) {
                head[v] = u;
                pos[v] = timer++;
            }
        }

        // Initialize segment tree
        for (int i = 0; i < n; i++) {
            updateSeg(
                1, 0, n - 1,
                pos[i],
                1 << (s[i] - 'a')
            );
        }

        vector<bool> ans;

        for (string &q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                s[u] = c;

                updateSeg(
                    1, 0, n - 1,
                    pos[u],
                    1 << (c - 'a')
                );
            }
            else {
                int u, v;
                ss >> u >> v;

                int mask = queryPath(u, v, n);

                ans.push_back(
                    (mask & (mask - 1)) == 0
                );
            }
        }

        return ans;
    }
};