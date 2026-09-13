class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int originalOnes = count(s.begin(), s.end(), '1');

        string t = "1" + s + "1";

        // Stores {character, length of its block}
        vector<pair<char, int>> blocks;

        for (char ch : t) {
            if (blocks.empty() || blocks.back().first != ch) {
                blocks.push_back({ch, 1});
            } else {
                blocks.back().second++;
            }
        }

        int maximumGain = 0;

        // Find a 1-block surrounded by zero blocks.
        for (int i = 1; i + 1 < blocks.size(); i++) {
            if (blocks[i].first == '1' &&
                blocks[i - 1].first == '0' &&
                blocks[i + 1].first == '0') {

                int gain = blocks[i - 1].second +
                           blocks[i + 1].second;

                maximumGain = max(maximumGain, gain);
            }
        }

        return originalOnes + maximumGain;
    }
};