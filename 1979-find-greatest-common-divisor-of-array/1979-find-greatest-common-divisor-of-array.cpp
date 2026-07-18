class Solution {
public:
    int findGCD(vector<int>& nums) {
        int smallest = *min_element(nums.begin(),nums.end());
        int greatest = *max_element(nums.begin(),nums.end());

        return gcd(smallest,greatest);
    }
};