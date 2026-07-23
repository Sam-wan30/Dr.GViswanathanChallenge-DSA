class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        // Special cases
        if (n <= 2) {
            return n;
        }

        // Find the smallest power of 2 strictly greater than n
        int answer = 1;

        while (answer <= n) {
            answer *= 2;
        }

        return answer;
    }
};