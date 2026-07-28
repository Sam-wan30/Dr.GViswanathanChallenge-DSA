class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> frequency(26, 0);

        for (char ch : s) {
            frequency[ch - 'a']++;
        }

        string firstHalf;
        char middle = '\0';

        for (int i = 0; i < 26; i++) {
            // Add half of each character to the left side
            firstHalf.append(frequency[i] / 2, char('a' + i));

            // The odd-frequency character belongs in the middle
            if (frequency[i] % 2 == 1) {
                middle = char('a' + i);
            }
        }

        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        if (middle != '\0') {
            return firstHalf + middle + secondHalf;
        }

        return firstHalf + secondHalf;
    }
};