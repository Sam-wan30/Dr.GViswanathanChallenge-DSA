class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> answer;
        string digits = "123456789";

        for (int length = 2; length <= 9; length++) {
            for (int start = 0; start + length <= 9; start++) {
                string current = digits.substr(start, length);
                int number = stoi(current);

                if (number >= low && number <= high) {
                    answer.push_back(number);
                }
            }
        }

        sort(answer.begin(), answer.end());
        return answer;
    }
};