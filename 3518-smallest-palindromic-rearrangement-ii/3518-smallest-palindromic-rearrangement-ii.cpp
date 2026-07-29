#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<long double> logFact;

    // Returns min(C(n, r), limit).
    long long combinationCapped(int n, int r, long long limit) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;

        r = min(r, n - r);

        long double logValue =
            logFact[n] - logFact[r] - logFact[n - r];

        // If the combination is definitely at least limit,
        // we do not need its exact value.
        if (logValue > log((long double)limit) + 1e-12L) {
            return limit;
        }

        long long result = 1;

        for (int i = 1; i <= r; i++) {
            __int128 next =
                (__int128)result * (n - r + i) / i;

            if (next >= limit) {
                return limit;
            }

            result = (long long)next;
        }

        return result;
    }

    // Returns min(number of distinct permutations, limit).
    long long countPermutations(
        const array<int, 26>& count,
        long long limit
    ) {
        long long ways = 1;
        int used = 0;

        /*
         Multinomial count:

         total! / (c1! * c2! * ...)

         It can be calculated as:

         C(c1, c1) *
         C(c1 + c2, c2) *
         C(c1 + c2 + c3, c3) * ...
        */
        for (int frequency : count) {
            if (frequency == 0) continue;

            long long required =
                (limit + ways - 1) / ways;

            long long choose = combinationCapped(
                used + frequency,
                frequency,
                required
            );

            if (choose >= required) {
                return limit;
            }

            ways *= choose;
            used += frequency;
        }

        return ways;
    }

public:
    string smallestPalindrome(string s, int k) {
        array<int, 26> frequency{};

        for (char ch : s) {
            frequency[ch - 'a']++;
        }

        array<int, 26> halfCount{};
        char middle = '\0';
        int halfLength = 0;

        for (int i = 0; i < 26; i++) {
            halfCount[i] = frequency[i] / 2;
            halfLength += halfCount[i];

            if (frequency[i] % 2 == 1) {
                middle = char('a' + i);
            }
        }

        // Precompute logarithms of factorials.
        logFact.resize(halfLength + 1, 0);

        for (int i = 1; i <= halfLength; i++) {
            logFact[i] = logFact[i - 1] + log((long double)i);
        }

        // Check whether at least k permutations exist.
        if (countPermutations(halfCount, k) < k) {
            return "";
        }

        string firstHalf;
        firstHalf.reserve(halfLength);

        /*
         Construct the k-th lexicographically smallest
         permutation of the first half.
        */
        for (int position = 0; position < halfLength; position++) {
            for (int character = 0; character < 26; character++) {
                if (halfCount[character] == 0) {
                    continue;
                }

                // Temporarily place this character.
                halfCount[character]--;

                long long ways =
                    countPermutations(halfCount, k);

                if (ways >= k) {
                    firstHalf.push_back(
                        char('a' + character)
                    );
                    break;
                }

                // Skip all permutations beginning with this character.
                k -= ways;
                halfCount[character]++;
            }
        }

        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        if (middle != '\0') {
            return firstHalf + string(1, middle) + secondHalf;
        }

        return firstHalf + secondHalf;
    }
};