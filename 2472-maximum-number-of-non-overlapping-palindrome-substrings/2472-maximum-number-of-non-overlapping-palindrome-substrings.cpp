class Solution {
public:
    bool isPalindrome(string &s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }

    int maxPalindromes(string s, int k) {
        int n = s.size();

        // dp[i] = maximum palindromes we can select
        // from the first i characters
        vector<int> dp(n + 1, 0);

        for (int i = k; i <= n; i++) {

            // Don't select a palindrome ending here
            dp[i] = dp[i - 1];

            // Check palindrome of length k
            if (isPalindrome(s, i - k, i - 1)) {
                dp[i] = max(dp[i], dp[i - k] + 1);
            }

            // Check palindrome of length k + 1
            if (i >= k + 1 &&
                isPalindrome(s, i - k - 1, i - 1)) {

                dp[i] = max(dp[i], dp[i - k - 1] + 1);
            }
        }

        return dp[n];
    }
};