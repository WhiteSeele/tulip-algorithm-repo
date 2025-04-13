#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-445/problems/smallest-palindromic-rearrangement-i/?slug=smallest-palindromic-rearrangement-ii&tab=description&region=local_v2
class Solution {
    public:
        string smallestPalindrome(string s) {
            int n = s.length();
            if(n == 1) return s;
            vector<int> cnt(26);
    
            for(auto c: s) {
                cnt[c - 'a'] ++ ;
            }
    
            int len = (n + 1) / 2;
            string ans = "";
            int id = 0, odd = -1;
            for(int i = 0; i < 26; i ++ ) {
                if(cnt[i] == 0) continue;
                if(cnt[i] % 2 == 1) {
                    odd = i;
                }
                for(int j = 0; j < cnt[i] / 2; j ++ ) {
                    ans += string(1, char('a' + i));
                }
            }
            string pos = string(ans.rbegin(), ans.rend());
            ans += pos;
            if(odd != -1) {
                char cen = char('a' + odd);
                ans.insert(ans.length() / 2, string(1, cen));
            }
            return ans;
        }
    };