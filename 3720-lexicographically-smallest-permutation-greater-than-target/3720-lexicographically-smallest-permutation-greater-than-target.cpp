class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        string ans;

        for (int i = 0; i < n; i++) {
            int cur = target[i] - 'a';

            if (freq[cur] > 0) {
                ans.push_back(target[i]);
                freq[cur]--;
            } 
            else {
                for (int c = cur + 1; c < 26; c++) {
                    if (freq[c] > 0) {
                        ans.push_back(char('a' + c));
                        freq[c]--;

                        for (int j = 0; j < 26; j++) {
                            while (freq[j] > 0) {
                                ans.push_back(char('a' + j));
                                freq[j]--;
                            }
                        }

                        return ans;
                    }
                }

                while (!ans.empty()) {
                    int pos = ans.size() - 1;

                    char removed = ans.back();
                    ans.pop_back();
                    freq[removed - 'a']++;

                    int need = target[pos] - 'a';

                    for (int c = need + 1; c < 26; c++) {
                        if (freq[c] > 0) {
                            ans.push_back(char('a' + c));
                            freq[c]--;

                            for (int j = 0; j < 26; j++) {
                                while (freq[j] > 0) {
                                    ans.push_back(char('a' + j));
                                    freq[j]--;
                                }
                            }

                            return ans;
                        }
                    }
                }

                return "";
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            char removed = ans.back();
            ans.pop_back();
            freq[removed - 'a']++;

            int need = target[i] - 'a';

            for (int c = need + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    ans.push_back(char('a' + c));
                    freq[c]--;

                    for (int j = 0; j < 26; j++) {
                        while (freq[j] > 0) {
                            ans.push_back(char('a' + j));
                            freq[j]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};