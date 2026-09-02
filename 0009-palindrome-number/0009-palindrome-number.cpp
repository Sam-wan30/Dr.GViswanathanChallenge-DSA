class Solution {
public:
    bool isPalindrome(int n) {
        if(n<0) return false;
        
        int original = n;
        long long revnum = 0;
        
        while(n>0){
            int ld = n%10;
            n = n/10;
            revnum = (revnum*10+ld);
        }
        
        if(revnum == original){
            return true;
        }
        return false;
    }
};