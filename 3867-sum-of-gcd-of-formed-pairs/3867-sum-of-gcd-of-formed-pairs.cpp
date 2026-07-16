class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefixGcd;
        prefixGcd.reserve(n);

        int prefixMaximum = 0;

        // Construct prefixGcd array
        for (int value : nums) {
            prefixMaximum = max(prefixMaximum, value);
            prefixGcd.push_back(gcd(value, prefixMaximum));
        }

        // Sort in non-decreasing order
        sort(prefixGcd.begin(), prefixGcd.end());

        long long answer = 0;
        int left = 0;
        int right = n - 1;

        // Pair smallest with largest
        while (left < right) {
            answer += gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return answer;
    }
};