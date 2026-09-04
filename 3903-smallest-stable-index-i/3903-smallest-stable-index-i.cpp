class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<long long> suffixMin(n);

        suffixMin[n - 1] = nums[n - 1];

        // Calculate suffix minimum
        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min((long long)nums[i], suffixMin[i + 1]);
        }

        long long prefixMax = nums[0];

        // Find first stable index
        for (int i = 0; i < n; i++) {
            prefixMax = max(prefixMax, (long long)nums[i]);

            long long instability = prefixMax - suffixMin[i];

            if (instability <= k) {
                return i;
            }
        }

        return -1;
    }
};