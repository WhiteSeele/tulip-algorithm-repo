#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/longest-palindrome-after-substring-concatenation-i/description/
class Solution {
    public:
        int longestPalindrome(string s, string t) {
            set<string> ssub;
            int n = s.length();
            ssub.insert("");
            for(int i = 0; i < n; i ++ ) {
                for(int j = i; j < n; j ++ ) {
                    ssub.insert(s.substr(i, j - i + 1));
                }
            }
            set<string> tsub;
            int m = t.length();
            tsub.insert("");
            for(int i = 0; i < m; i ++ ) {
                for(int j = i; j < m; j ++ ) {
                    tsub.insert(t.substr(i, j - i + 1));
                }
            }
            int ans = 0;
            auto isP = [](string s) -> bool {
                int i = 0, j = s.length() - 1;
                while(i < j) {
                    if(s[i] != s[j]) return false;
                    i ++ ;
                    j -- ;
                }
                return true;
            };
            for(auto& ss: ssub) {
                for(auto& ts: tsub) {
                    string news = ss + ts;
                    if(isP(news)) {
                        ans = max(ans, (int)ss.size() +(int)ts.size());
                    }
                }
            }
            return ans;
        }
    };