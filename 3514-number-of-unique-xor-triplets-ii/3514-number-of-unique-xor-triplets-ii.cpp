class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAX_XOR = 2048;

        vector<bool> present(MAX_XOR, false);
        vector<int> values;

        // Remove duplicate values
        for (int num : nums) {
            if (!present[num]) {
                present[num] = true;
                values.push_back(num);
            }
        }

        vector<bool> pairXor(MAX_XOR, false);
        vector<bool> tripletXor(MAX_XOR, false);

        // Find all possible XOR values of two elements
        for (int x : values) {
            for (int y : values) {
                pairXor[x ^ y] = true;
            }
        }

        // Combine every pair XOR with a third element
        for (int xorValue = 0; xorValue < MAX_XOR; xorValue++) {
            if (!pairXor[xorValue])
                continue;

            for (int z : values) {
                tripletXor[xorValue ^ z] = true;
            }
        }

        int answer = 0;

        for (bool possible : tripletXor) {
            if (possible)
                answer++;
        }

        return answer;
    }
};