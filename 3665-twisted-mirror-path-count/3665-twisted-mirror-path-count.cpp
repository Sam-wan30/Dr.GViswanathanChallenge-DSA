class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> right(m, vector<int>(n, 0));
        vector<vector<int>> down(m, vector<int>(n, 0));

        // Initialize the first moves separately
        if (n > 1)
            right[0][1] = 1;

        if (m > 1)
            down[1][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                long long r = right[i][j];
                long long d = down[i][j];

                if (grid[i][j] == 0) {
                    // Empty cell: can move right or down
                    long long total = (r + d) % MOD;

                    if (j + 1 < n) {
                        right[i][j + 1] =
                            (right[i][j + 1] + total) % MOD;
                    }

                    if (i + 1 < m) {
                        down[i + 1][j] =
                            (down[i + 1][j] + total) % MOD;
                    }
                }
                else {
                    // Mirror: right becomes down
                    if (i + 1 < m) {
                        down[i + 1][j] =
                            (down[i + 1][j] + r) % MOD;
                    }

                    // Mirror: down becomes right
                    if (j + 1 < n) {
                        right[i][j + 1] =
                            (right[i][j + 1] + d) % MOD;
                    }
                }
            }
        }

        return (right[m - 1][n - 1] +
                down[m - 1][n - 1]) % MOD;
    }
};