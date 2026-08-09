class Solution {
public:
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(vector<int>& piles, int i, int M) {
        int n = piles.size();

        if (i >= n) {
            return 0;
        }

        if (i + 2 * M >= n) {
            return suffix[i];
        }

        if (dp[i][M] != -1) {
            return dp[i][M];
        }

        int best = 0;

        for (int x = 1; x <= 2 * M; x++) {
            int opponent = solve(piles, i + x, max(M, x));

            int current = suffix[i] - opponent;

            best = max(best, current);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(piles, 0, 1);
    }
};