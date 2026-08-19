class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, unordered_set<int>> mp;

        for (auto &seat : reservedSeats) {
            mp[seat[0]].insert(seat[1]);
        }

        long long ans = 2LL * n;

        for (auto &row : mp) {
            auto &s = row.second;

            bool left = true;
            bool middle = true;
            bool right = true;

            // seats 2,3,4,5
            for (int seat = 2; seat <= 5; seat++) {
                if (s.count(seat)) {
                    left = false;
                    break;
                }
            }

            // seats 4,5,6,7
            for (int seat = 4; seat <= 7; seat++) {
                if (s.count(seat)) {
                    middle = false;
                    break;
                }
            }

            // seats 6,7,8,9
            for (int seat = 6; seat <= 9; seat++) {
                if (s.count(seat)) {
                    right = false;
                    break;
                }
            }

            int families = 0;

            if (left && right)
                families = 2;
            else if (left || middle || right)
                families = 1;

            // Earlier we assumed this row could fit 2 families
            ans -= 2;
            ans += families;
        }

        return ans;
    }
};