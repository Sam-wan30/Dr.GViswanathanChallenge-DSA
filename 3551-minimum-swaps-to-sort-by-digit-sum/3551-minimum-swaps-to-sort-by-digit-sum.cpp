class Solution {
public:
    int digitSum(int num) {
        int sum = 0;

        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;

        sort(sorted.begin(), sorted.end(), [&](int a, int b) {
            int sumA = digitSum(a);
            int sumB = digitSum(b);

            if (sumA == sumB)
                return a < b;

            return sumA < sumB;
        });

        unordered_map<int, int> pos;

        for (int i = 0; i < n; i++) {
            pos[sorted[i]] = i;
        }

        vector<bool> visited(n, false);

        int swaps = 0;

        for (int i = 0; i < n; i++) {

            if (visited[i] || pos[nums[i]] == i)
                continue;

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = pos[nums[j]];
                cycleSize++;
            }

            swaps += cycleSize - 1;
        }

        return swaps;
    }
};