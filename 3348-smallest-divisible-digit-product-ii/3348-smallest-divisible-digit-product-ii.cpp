class Solution {
public:
    using State = array<int, 4>;

    vector<State> f = {
        {0,0,0,0},
        {0,0,0,0},
        {1,0,0,0},
        {0,1,0,0},
        {2,0,0,0},
        {0,0,1,0},
        {1,1,0,0},
        {0,0,0,1},
        {3,0,0,0},
        {0,2,0,0}
    };

    map<State, int> memo;

    State removeFactor(State s, int d) {
        for (int i = 0; i < 4; i++)
            s[i] = max(0, s[i] - f[d][i]);
        return s;
    }

    int need(State s) {
        if (s == State{0,0,0,0})
            return 0;

        if (memo.count(s))
            return memo[s];

        int ans = 1e9;

        for (int d = 2; d <= 9; d++) {
            State nxt = removeFactor(s, d);

            if (nxt != s)
                ans = min(ans, 1 + need(nxt));
        }

        return memo[s] = ans;
    }

    string build(int len, State req) {
        string ans;

        while (len--) {
            for (int d = 1; d <= 9; d++) {
                State nxt = removeFactor(req, d);

                if (need(nxt) <= len) {
                    ans += char('0' + d);
                    req = nxt;
                    break;
                }
            }
        }

        return ans;
    }

    string smallestNumber(string num, long long t) {
        State req = {0,0,0,0};

        int p[4] = {2,3,5,7};

        for (int i = 0; i < 4; i++) {
            while (t % p[i] == 0) {
                req[i]++;
                t /= p[i];
            }
        }

        if (t != 1)
            return "-1";

        int n = num.size();

        vector<State> pref(n + 1);
        vector<bool> zero(n + 1, false);

        pref[0] = req;

        for (int i = 0; i < n; i++) {
            zero[i + 1] = zero[i] || num[i] == '0';

            if (num[i] == '0')
                pref[i + 1] = pref[i];
            else
                pref[i + 1] = removeFactor(pref[i], num[i] - '0');
        }

        if (!zero[n] && need(pref[n]) == 0)
            return num;

        for (int i = n - 1; i >= 0; i--) {
            if (zero[i])
                continue;

            int start = max(1, num[i] - '0' + 1);

            for (int d = start; d <= 9; d++) {
                State nxt = removeFactor(pref[i], d);
                int left = n - i - 1;

                if (need(nxt) <= left) {
                    return num.substr(0, i) +
                           char('0' + d) +
                           build(left, nxt);
                }
            }
        }

        int len = max(n + 1, need(req));

        return build(len, req);
    }
};