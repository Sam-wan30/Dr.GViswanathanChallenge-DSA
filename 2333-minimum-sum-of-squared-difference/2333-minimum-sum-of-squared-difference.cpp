class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {

        int n = nums1.size();
        vector<int> diff(n);

        long long k = (long long)k1 + k2;
        long long sum = 0;

        int maxi = 0;

        for(int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            sum += diff[i];
            maxi = max(maxi, diff[i]);
        }

        if(sum <= k)
            return 0;

        int low = 0, high = maxi;

        while(low < high) {
            int mid = low + (high - low) / 2;

            long long operations = 0;

            for(int x : diff) {
                if(x > mid)
                    operations += x - mid;
            }

            if(operations <= k)
                high = mid;
            else
                low = mid + 1;
        }

        long long ans = 0;
        long long remaining = k;

        for(int x : diff) {
            if(x > low) {
                remaining -= x - low;
                x = low;
            }

            ans += 1LL * x * x;
        }

        // Use remaining operations to reduce some values
        // from low to low-1.
        ans -= remaining * (2LL * low - 1);

        return ans;
    }
};