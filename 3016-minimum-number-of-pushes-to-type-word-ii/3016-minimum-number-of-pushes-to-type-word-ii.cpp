class Solution {
public:
    int minimumPushes(string word) {
        vector<int> frequency(26, 0);

        for (char ch : word) {
            frequency[ch - 'a']++;
        }

        sort(frequency.rbegin(), frequency.rend());

        int answer = 0;

        for (int i = 0; i < 26; i++) {
            int pushes = (i / 8) + 1;

            answer += frequency[i] * pushes;
        }

        return answer;
    }
};