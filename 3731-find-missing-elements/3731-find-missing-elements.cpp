class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        unordered_set<int> present(nums.begin(), nums.end());

        int minimum = *min_element(nums.begin(), nums.end());
        int maximum = *max_element(nums.begin(), nums.end());

        vector<int> missing;

        for (int value = minimum; value <= maximum; value++) {
            if (present.find(value) == present.end()) {
                missing.push_back(value);
            }
        }

        return missing;
    }
};