class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxValue = *max_element(nums.begin(), nums.end());

        vector<long long> frequency(maxValue + 1, 0);

        for (int num : nums) {
            frequency[num]++;
        }

        // divisibleCount[g] = how many numbers are divisible by g
        vector<long long> divisibleCount(maxValue + 1, 0);

        for (int g = 1; g <= maxValue; g++) {
            for (int multiple = g; multiple <= maxValue; multiple += g) {
                divisibleCount[g] += frequency[multiple];
            }
        }

        // exactPairs[g] = number of pairs whose GCD is exactly g
        vector<long long> exactPairs(maxValue + 1, 0);

        for (int g = maxValue; g >= 1; g--) {
            long long count = divisibleCount[g];

            // All pairs where both numbers are divisible by g
            exactPairs[g] = count * (count - 1) / 2;

            // Remove pairs whose GCD is a larger multiple of g
            for (int multiple = 2 * g;
                 multiple <= maxValue;
                 multiple += g) {
                exactPairs[g] -= exactPairs[multiple];
            }
        }

        // prefix[g] = number of pairs with GCD <= g
        vector<long long> prefix(maxValue + 1, 0);

        for (int g = 1; g <= maxValue; g++) {
            prefix[g] = prefix[g - 1] + exactPairs[g];
        }

        vector<int> answer;

        for (long long query : queries) {
            // Find the first GCD whose cumulative count exceeds query
            int gcdValue = upper_bound(
                prefix.begin(),
                prefix.end(),
                query
            ) - prefix.begin();

            answer.push_back(gcdValue);
        }

        return answer;
    }
};
