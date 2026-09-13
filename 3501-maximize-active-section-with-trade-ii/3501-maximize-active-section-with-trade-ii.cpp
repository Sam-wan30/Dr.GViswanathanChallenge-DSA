class Solution {
private:
    class SegmentTree {
        int n;
        vector<int> tree;

        void build(int node, int left, int right,
                   const vector<int>& values) {
            if (left == right) {
                tree[node] = values[left];
                return;
            }

            int mid = left + (right - left) / 2;

            build(node * 2, left, mid, values);
            build(node * 2 + 1, mid + 1, right, values);

            tree[node] = max(tree[node * 2],
                             tree[node * 2 + 1]);
        }

        int query(int node, int left, int right,
                  int queryLeft, int queryRight) {
            if (queryLeft <= left && right <= queryRight) {
                return tree[node];
            }

            if (right < queryLeft || queryRight < left) {
                return 0;
            }

            int mid = left + (right - left) / 2;

            return max(
                query(node * 2, left, mid,
                      queryLeft, queryRight),
                query(node * 2 + 1, mid + 1, right,
                      queryLeft, queryRight)
            );
        }

    public:
        SegmentTree(const vector<int>& values) {
            n = values.size();

            if (n > 0) {
                tree.resize(4 * n);
                build(1, 0, n - 1, values);
            }
        }

        int query(int left, int right) {
            if (n == 0 || left > right) {
                return 0;
            }

            return query(1, 0, n - 1, left, right);
        }
    };

public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        // Initial number of active sections in the whole string.
        int totalOnes = count(s.begin(), s.end(), '1');

        /*
         * For every globally surrounded 1-block, store:
         *
         * start[i]     = first index of the 1-block
         * end[i]       = last index of the 1-block
         * leftZeros[i] = adjacent zero-block length
         * rightZeros[i]= adjacent zero-block length
         * gain[i]      = leftZeros[i] + rightZeros[i]
         */
        vector<int> start;
        vector<int> finish;
        vector<int> leftZeros;
        vector<int> rightZeros;
        vector<int> gain;

        int i = 0;

        while (i < n) {
            if (s[i] == '0') {
                i++;
                continue;
            }

            int oneStart = i;

            while (i < n && s[i] == '1') {
                i++;
            }

            int oneEnd = i - 1;

            // The 1-block must have a zero on both sides.
            if (oneStart > 0 &&
                oneEnd + 1 < n &&
                s[oneStart - 1] == '0' &&
                s[oneEnd + 1] == '0') {

                int left = oneStart - 1;

                while (left >= 0 && s[left] == '0') {
                    left--;
                }

                int right = oneEnd + 1;

                while (right < n && s[right] == '0') {
                    right++;
                }

                int leftLength = oneStart - left - 1;
                int rightLength = right - oneEnd - 1;

                start.push_back(oneStart);
                finish.push_back(oneEnd);
                leftZeros.push_back(leftLength);
                rightZeros.push_back(rightLength);
                gain.push_back(leftLength + rightLength);
            }
        }

        SegmentTree segmentTree(gain);

        vector<int> answer;
        int blocks = start.size();

        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];

            /*
             * An eligible 1-block must be strictly inside [l, r]:
             *
             * start > l
             * finish < r
             *
             * This guarantees at least one zero from the substring
             * exists on both sides of the 1-block.
             */

            int first = upper_bound(
                start.begin(),
                start.end(),
                l
            ) - start.begin();

            int last = lower_bound(
                finish.begin(),
                finish.end(),
                r
            ) - finish.begin() - 1;

            // No eligible 1-block in this query.
            if (first >= blocks ||
                last < 0 ||
                first > last ||
                finish[first] >= r ||
                start[last] <= l) {
                answer.push_back(totalOnes);
                continue;
            }

            int bestGain = 0;

            /*
             * First eligible block:
             * its left zero-block may be cut by l.
             */
            int firstLeftContribution =
                min(leftZeros[first], start[first] - l);

            int firstRightContribution =
                min(rightZeros[first], r - finish[first]);

            bestGain = max(
                bestGain,
                firstLeftContribution +
                firstRightContribution
            );

            /*
             * Last eligible block:
             * its right zero-block may be cut by r.
             */
            if (last != first) {
                int lastLeftContribution =
                    min(leftZeros[last], start[last] - l);

                int lastRightContribution =
                    min(rightZeros[last], r - finish[last]);

                bestGain = max(
                    bestGain,
                    lastLeftContribution +
                    lastRightContribution
                );
            }

            /*
             * Blocks strictly between first and last cannot have
             * their adjacent zero-blocks cut by query boundaries.
             */
            if (first + 1 <= last - 1) {
                bestGain = max(
                    bestGain,
                    segmentTree.query(first + 1, last - 1)
                );
            }

            answer.push_back(totalOnes + bestGain);
        }

        return answer;
    }
};