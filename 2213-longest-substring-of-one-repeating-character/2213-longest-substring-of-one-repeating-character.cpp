class Solution {
public:
    struct Node {
        int len;
        int pref;
        int suff;
        int best;

        char leftChar;
        char rightChar;
    };

    vector<Node> tree;
    string s;

    Node merge(Node left, Node right) {
        if (left.len == 0) return right;
        if (right.len == 0) return left;

        Node result;

        result.len = left.len + right.len;
        result.leftChar = left.leftChar;
        result.rightChar = right.rightChar;

        result.pref = left.pref;

        if (left.pref == left.len &&
            left.rightChar == right.leftChar) {

            result.pref = left.len + right.pref;
        }

        result.suff = right.suff;

        if (right.suff == right.len &&
            left.rightChar == right.leftChar) {

            result.suff = right.len + left.suff;
        }

        result.best = max(left.best, right.best);

        if (left.rightChar == right.leftChar) {
            result.best = max(
                result.best,
                left.suff + right.pref
            );
        }

        return result;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {
                1, 1, 1, 1,
                s[l], s[l]
            };

            return;
        }

        int mid = l + (r - l) / 2;

        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);

        tree[node] = merge(
            tree[2 * node],
            tree[2 * node + 1]
        );
    }

    void update(int node, int l, int r,
                int index, char ch) {

        if (l == r) {
            s[index] = ch;

            tree[node] = {
                1, 1, 1, 1,
                ch, ch
            };

            return;
        }

        int mid = l + (r - l) / 2;

        if (index <= mid) {
            update(2 * node, l, mid, index, ch);
        }
        else {
            update(
                2 * node + 1,
                mid + 1,
                r,
                index,
                ch
            );
        }

        tree[node] = merge(
            tree[2 * node],
            tree[2 * node + 1]
        );
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        this->s = s;

        int n = s.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> answer;

        for (int i = 0; i < queryIndices.size(); i++) {

            update(
                1,
                0,
                n - 1,
                queryIndices[i],
                queryCharacters[i]
            );

            answer.push_back(tree[1].best);
        }

        return answer;
    }
};