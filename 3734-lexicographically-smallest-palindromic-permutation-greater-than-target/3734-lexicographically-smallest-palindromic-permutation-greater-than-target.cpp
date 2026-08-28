class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        int odd = 0, mid = -1;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = i;
            }
        }

        if (odd > 1)
            return "";

        if (s.size() % 2 == 1) {
            cnt[mid]--;
        }

        int n = s.size();
        int half = n / 2;

        string left;

        int i = 0;

        for (; i < half; i++) {
            int c = target[i] - 'a';

            cnt[c] -= 2;
            left.push_back(target[i]);

            if (cnt[c] < 0)
                break;
        }

        if (i == half) {
            string ans = left;

            if (n % 2)
                ans += char('a' + mid);

            string rev = left;
            reverse(rev.begin(), rev.end());

            ans += rev;

            if (ans > target)
                return ans;
        }

        while (!left.empty()) {
            int c = left.back() - 'a';
            left.pop_back();

            cnt[c] += 2;

            for (int j = c + 1; j < 26; j++) {
                if (cnt[j] >= 2) {
                    cnt[j] -= 2;
                    left.push_back(char('a' + j));

                    for (int k = 0; k < 26; k++) {
                        while (cnt[k] >= 2) {
                            cnt[k] -= 2;
                            left.push_back(char('a' + k));
                        }
                    }

                    string ans = left;

                    if (n % 2)
                        ans += char('a' + mid);

                    string rev = left;
                    reverse(rev.begin(), rev.end());

                    ans += rev;

                    return ans;
                }
            }
        }

        return "";
    }
};