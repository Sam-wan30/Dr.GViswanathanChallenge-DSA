class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;

        vector<int> bits(31, 0);

        // Step 1: Count set bits
        for (int num : nums) {
            for (int j = 0; j < 31; j++) {
                if (num & (1 << j)) {
                    bits[j]++;
                }
            }
        }

        long long ans = 0;

        // Step 2: Construct k maximum numbers
        for (int i = 0; i < k; i++) {
            long long num = 0;

            for (int j = 0; j < 31; j++) {
                if (bits[j] > 0) {
                    num += (1LL << j);
                    bits[j]--;
                }
            }

            // Step 3: Add square
            ans = (ans + num * num) % MOD;
        }

        return ans;
    }
};