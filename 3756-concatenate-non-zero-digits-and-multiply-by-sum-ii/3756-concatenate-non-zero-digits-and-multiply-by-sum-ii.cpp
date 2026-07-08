class Solution {
public:
    static const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> cnt(n + 1, 0);
        vector<long long> digitSum(n + 1, 0);

        vector<int> digits;
        digits.push_back(0); // 1-based indexing

        for (int i = 0; i < n; i++) {
            cnt[i + 1] = cnt[i];
            digitSum[i + 1] = digitSum[i];

            if (s[i] != '0') {
                cnt[i + 1]++;
                int d = s[i] - '0';
                digits.push_back(d);
                digitSum[i + 1] += d;
            }
        }

        int k = digits.size() - 1;

        vector<long long> pow10(k + 1, 1);
        for (int i = 1; i <= k; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        vector<long long> hash(k + 1, 0);
        for (int i = 1; i <= k; i++) {
            hash[i] = (hash[i - 1] * 10 + digits[i]) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int left = cnt[l] + 1;
            int right = cnt[r + 1];

            if (left > right) {
                ans.push_back(0);
                continue;
            }

            int len = right - left + 1;

            long long x = (hash[right] - hash[left - 1] * pow10[len]) % MOD;
            if (x < 0) x += MOD;

            long long sum = digitSum[r + 1] - digitSum[l];

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};