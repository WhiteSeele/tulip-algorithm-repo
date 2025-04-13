#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/smallest-palindromic-rearrangement-ii/

/*
    回文串只需要关心左半部分即可
    s 长度为奇数正中间字母 c 恰好出现奇数次，重排后的回文串也是出现奇数次，中间也必须是 c
    所以无论 s 长度为奇数还是偶数，都只需要考虑左半部分（奇数去掉回文中心）

    试填法：
    最左边能不能填 a ？ 如果不能试试 b，c，...，z
    如何判断 ？ 假设最左侧字母填 a，问题变为计算剩余位置的字符串排列个数 p，如果 p < k，说明 k 太大，最左侧不能填 a
    如果 p >= k, 说明最左侧填 a 后右边足以容纳至少 k 个排列，最左边就是字母 a

    如何计算 ？
    假设字母 a 有 2 个，字母 b 有 3 个
    先从 sz 个位置中选出 2 个位置填字母 a，方案数为C(sz, 2)；再从剩下的 sz - 2 个字母中选 3 个位置填字母 b，方案数为
    C(sz - 2, 3)，以此类推
    根据乘法原理，排列数为这 26 个组合数的乘积。
*/
class Solution {
    public:
        string smallestPalindrome(string s, int k) {
            int n = s.length();

            int m = n / 2;
            vector<int> cnt(26);
            for(int i = 0; i < m; i ++ ) {
                cnt[s[i] - 'a'] ++ ;
            }

            auto comb = [&](int n, int m) -> int {
                m = min(m, n - m);                //C(n, m) = C(n, n - m) 恒等式
                long long res = 1;
                for(int i = 1; i <= m; i ++ ) {
                    res = res * (n + 1 - i) / i;
                    if(res >= k) {
                        return k;
                    }
                }
                return res;
            };

            //计算长度为 sz 的字符串的排列个数
            auto perm = [&](int sz) -> int {
                long long res = 1;
                for(int c: cnt) {
                    if(c == 0) continue;
                    res *= comb(sz, c);
                    if(res >= k) return k;
                    //从剩余位置中选位置填下一个字母
                    sz -= c;
                }
                return res;
            };

            if(perm(m) < k) return ""; //k 太大

            string left(m, 0);
            for(int i = 0; i < m; i ++ ) {
                for(int j = 0; j < 26; j ++ ) {
                    if(cnt[j] == 0) continue;
                    cnt[j] -- ;
                    int p = perm(m - i - 1);
                    if(p >= k) {    //足够有 k 个排列，可以填 'a' + j
                        left[i] = 'a' + j;
                        break;
                    }
                    k -= p;       //k 太大，要填更大的字母
                    cnt[j] ++ ;
                }
            }
            string ans = left;
            if(n % 2) {
                ans += s[n / 2];
            }
            ranges::reverse(left);
            return ans + left;
        }
    };