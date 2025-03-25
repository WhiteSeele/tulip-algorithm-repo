#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/minimum-operations-to-make-array-elements-zero/description/?slug=minimum-operations-to-make-array-elements-zero&region=local_v2
class Solution {
    public:
        long long f(unsigned int r) {
            int m = bit_width(r);
    
            long long res = 0;
            for(int i = 1; i <= m - 1; i ++ ) {
                res += (long long)(1 << (i - 1)) * ((i + 1) / 2);
            }
    
            return res + (r - (1 << m >> 1) + 1) * 1LL * ((m + 1) / 2);
    
        }

        long long minOperations(vector<vector<int>>& queries) {
            long long ans = 0;
    
            for(auto& q: queries) {
                ans += (f(q[1]) - f(q[0] - 1) + 1) / 2;
            }
    
            return ans;
        }
    };