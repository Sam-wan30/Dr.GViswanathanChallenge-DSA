class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;

        bool inc = true, dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[(i + 1) % n] != (nums[i] + 1) % n)
                inc = false;

            if (nums[(i + 1) % n] != (nums[i] - 1 + n) % n)
                dec = false;
        }

        // Case 1: Cyclically increasing
        if (inc) {
            int k = (n - nums[0]) % n;

            ans = min(ans, k);

            // Reverse -> Rotate -> Reverse
            ans = min(ans, n - k + 2);
        }

        // Case 2: Cyclically decreasing
        if (dec) {
            // Reverse first, then rotate
            int k1 = (nums[0] + 1) % n;
            ans = min(ans, 1 + k1);

            // Rotate first, then reverse
            int k2 = (n - 1 - nums[0] + n) % n;
            ans = min(ans, 1 + k2);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};