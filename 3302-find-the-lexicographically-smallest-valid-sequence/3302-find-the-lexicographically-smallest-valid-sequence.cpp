class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> suffix(m, -1);

        int i = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            while (i >= 0 && word1[i] != word2[j]) {
                i--;
            }

            if (i < 0) break;

            suffix[j] = i;
            i--;
        }

        vector<int> ans;

        i = 0;
        int j = 0;
        bool changed = false;

        while (i < n && j < m) {

            if (word1[i] == word2[j]) {
                ans.push_back(i);
                i++;
                j++;
            }
            else if (!changed &&
                     (j == m - 1 ||
                     (suffix[j + 1] != -1 && i < suffix[j + 1]))) {

                ans.push_back(i);
                changed = true;
                i++;
                j++;
            }
            else {
                i++;
            }
        }

        if (j != m) {
            return {};
        }

        return ans;
    }
};