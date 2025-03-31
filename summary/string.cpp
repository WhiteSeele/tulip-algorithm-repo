/* 字符串相关 */

//回文串
/*
    区间DP: 
    class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.length();
        if(n<2){
            return s;
        }
        vector<vector<bool>> g(n,vector<bool>(n,false));
        for(int i=0;i<n;++i){
            g[i][i]=true;
        }
        for(int i=n-1;i>=0;--i){
            for(int j=i+1;j<n;++j){
                if(j-i+1>=3){
                    g[i][j]=(g[i+1][j-1])&&(s[i]==s[j]);
                }
                else{
                    g[i][j]=(s[i]==s[j]);
                }   
            }
        }
        int maxlen=0;
        string ans="";
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(g[i][j]==true){
                    if(maxlen<(j-i+1)){
                        maxlen=j-i+1;
                        ans=s.substr(i,j-i+1);
                    }
                }
            }
        }
        return ans;
    }
};
    中心扩展法求最长回文子串（LC5 https://leetcode.cn/problems/longest-palindromic-substring/description/）：
    class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        int l = INT_MAX / 4, r = INT_MIN / 4;
        auto expand = [&s](int left, int right) -> pair<int, int> {
            while(left >= 0 && right < s.length() && s[left] == s[right]) {
                -- left;
                ++ right;
            }
            return {left + 1, right - 1};
        };
        
        for(int i = 0; i < 2 * n - 1; i ++ ) {
            int l = i / 2, r = (i + 1) / 2;
            while(l >= 0 && r < n && s[l] == s[r]) {
                l -- ;
                r ++ ;
            }
        }
        // for(int i = 0; i < n; i ++ ) {
        //     auto [l1, r1] = expand(i, i);
        //     auto [l2, r2] = expand(i, i + 1);

        //     if(r1 - l1 > r - l) {
        //         l = l1;
        //         r = r1;
        //     }
        //     if(r2 - l2 > r - l) {
        //         l = l2;
        //         r = r2;
        //     }
        // }

        return s.substr(l, r - l + 1);
    }
};
*/