class Solution {
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int>& nums) {
        const int MAX_GCD = 200;

        vector<vector<int>> dp(
            MAX_GCD + 1,
            vector<int>(MAX_GCD + 1, 0)
        );

        dp[0][0] = 1;

        for (int num : nums) {
            vector<vector<int>> next = dp;

            for (int gcd1 = 0; gcd1 <= MAX_GCD; gcd1++) {
                for (int gcd2 = 0; gcd2 <= MAX_GCD; gcd2++) {
                    if (dp[gcd1][gcd2] == 0) {
                        continue;
                    }

                    int newGcd1 = std::gcd(gcd1, num);
                    int newGcd2 = std::gcd(gcd2, num);

                    // Add num to seq1
                    next[newGcd1][gcd2] =
                        (next[newGcd1][gcd2] + dp[gcd1][gcd2]) % MOD;

                    // Add num to seq2
                    next[gcd1][newGcd2] =
                        (next[gcd1][newGcd2] + dp[gcd1][gcd2]) % MOD;
                }
            }

            dp = move(next);
        }

        long long answer = 0;

        for (int gcdValue = 1; gcdValue <= MAX_GCD; gcdValue++) {
            answer = (answer + dp[gcdValue][gcdValue]) % MOD;
        }

        return answer;
    }
};