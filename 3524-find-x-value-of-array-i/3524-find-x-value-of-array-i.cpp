class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> next(k, 0);

            int val = num % k;

            // Start a new subarray with only num
            next[val]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * val) % k;
                next[newRemainder] += dp[r];
            }

            // Add subarrays ending here to final answer
            for (int r = 0; r < k; r++) {
                result[r] += next[r];
            }

            dp = next;
        }

        return result;
    }
};