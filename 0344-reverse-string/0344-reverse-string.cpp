class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0;
        reverseString(s,i);  
    }
    void reverseString(vector<char>& s,int i){
    if(i>=s.size()/2)
        return ;
        
    swap(s[i],s[s.size()-i-1]);
    reverseString(s, i+1);
    }

};