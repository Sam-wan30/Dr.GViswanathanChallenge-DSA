class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long squareSum = 0;
        long long lazy = 0;
    };

    vector<Node> seg;

    void apply(int idx, int l, int r, long long val) {
        long long len = r - l + 1;

        seg[idx].squareSum = (
            seg[idx].squareSum +
            2 * val % MOD * seg[idx].sum % MOD +
            len * val % MOD * val % MOD
        ) % MOD;

        seg[idx].sum = (
            seg[idx].sum + len * val
        ) % MOD;

        seg[idx].lazy = (seg[idx].lazy + val) % MOD;
    }

    void push(int idx, int l, int r) {
        if (seg[idx].lazy == 0 || l == r)
            return;

        int mid = l + (r - l) / 2;

        apply(idx * 2, l, mid, seg[idx].lazy);
        apply(idx * 2 + 1, mid + 1, r, seg[idx].lazy);

        seg[idx].lazy = 0;
    }

    void update(int idx, int l, int r,
                int ql, int qr, long long val) {

        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            apply(idx, l, r, val);
            return;
        }

        push(idx, l, r);

        int mid = l + (r - l) / 2;

        update(idx * 2, l, mid, ql, qr, val);
        update(idx * 2 + 1, mid + 1, r, ql, qr, val);

        seg[idx].sum = (
            seg[idx * 2].sum +
            seg[idx * 2 + 1].sum
        ) % MOD;

        seg[idx].squareSum = (
            seg[idx * 2].squareSum +
            seg[idx * 2 + 1].squareSum
        ) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        seg.assign(4 * n + 5, Node());

        vector<int> last(100001, -1);

        long long ans = 0;

        for (int i = 0; i < n; i++) {

            int start = last[nums[i]] + 1;

            update(1, 0, n - 1, start, i, 1);

            ans = (
                ans + seg[1].squareSum
            ) % MOD;

            last[nums[i]] = i;
        }

        return (int)ans;
    }
};