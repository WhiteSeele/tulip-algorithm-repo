#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/longest-palindrome-after-substring-concatenation-ii/description/
/*
    从 s 中选出一个子串为 x，t 中选出一个子串为 y 。答案要的子串为 x + y
    |x| 表示 x 的长度
    如果 |x| == |y|，那么就是 s 和 reverse(t) 的最长公共子串
    如果 |x| > |y|，那么 x 分为两个部分: ty + x'，其中 x' 是一个回文串，ty = reverse(y)
    枚举x'，也就是枚举 s 中的最长回文子串，假设为 s[l:r]，那么再加上s[0:l-1]与rt的最长公共子串的长度即为答案。
    枚举最长回文串可以用 中心扩展法 。
*/
class Solution {
    public:
        int foo(const string& s, const string& t) {
            int n = s.length(), m = t.length();
    
            vector<int> mx(n + 1);
            string rt = string(t.rbegin(), t.rend());
            vector f(n + 1, vector<int>(m + 1));
    
            //|x|=|y|
            for(int i = 0; i < n; i ++ ) {
                for(int j = 0; j < m; j ++ ) {
                    if(s[i] == rt[j]) {
                        f[i + 1][j + 1] = f[i][j] + 1;
                    }
                }
                mx[i + 1] = ranges::max(f[i + 1]);
            }
    
            int ans = ranges::max(mx) * 2;        //|x| = |y| 时的答案
    
            //|x| > |y|，中心扩展枚举s中的回文部分
            for(int i = 0; i < 2 * n - 1; i ++ ) {
                int l = i / 2, r = (i + 1) / 2;
                while(l >= 0 && r < n && s[l] == s[r]) {
                    l -- ;
                    r ++ ;
                }
                if(l + 1 <= r - 1) {
                    ans = max(ans, r - l - 1 + 2 * mx[l + 1]);
                }
            }
            return ans;
        }
    
        int longestPalindrome(string s, string t) {
            string rs = string(s.rbegin(), s.rend());
            string rt = string(t.rbegin(), t.rend());
    
            return max(foo(s, t), foo(rt, rs));
        }
    };