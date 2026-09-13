class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // dp[i] = maximum score difference achievable
        // starting from index i
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            int currentSum = 0;
            dp[i] = INT_MIN;

            // Take 1, 2, or 3 stones
            for (int j = i; j < n && j < i + 3; j++) {
                currentSum += stoneValue[j];

                dp[i] = max(
                    dp[i],
                    currentSum - dp[j + 1]
                );
            }
        }

        if (dp[0] > 0)
            return "Alice";
        else if (dp[0] < 0)
            return "Bob";
        else
            return "Tie";
    }
};