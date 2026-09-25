#include <bits/stdc++.h>
using namespace std;

class Solution {
    string s;
    int pos;

    // Combines two sets by concatenating every string
    // from A with every string from B.
    set<string> multiply(const set<string>& A, const set<string>& B) {
        set<string> result;

        for (const string& x : A) {
            for (const string& y : B) {
                result.insert(x + y);
            }
        }

        return result;
    }

    // Parses a sequence of expressions joined by commas.
    set<string> parseExpression() {
        set<string> result = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;  // skip ','

            set<string> next = parseTerm();

            // Union
            result.insert(next.begin(), next.end());
        }

        return result;
    }

    // Parses concatenated expressions.
    set<string> parseTerm() {
        set<string> result = {""};

        while (pos < s.size() &&
               s[pos] != '}' &&
               s[pos] != ',') {

            set<string> current;

            if (s[pos] == '{') {
                pos++;  // skip '{'

                current = parseExpression();

                pos++;  // skip '}'
            }
            else {
                // Single lowercase letter
                current.insert(string(1, s[pos]));
                pos++;
            }

            result = multiply(result, current);
        }

        return result;
    }

public:
    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> result = parseExpression();

        return vector<string>(result.begin(), result.end());
    }
};