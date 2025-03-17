#include<bits/stdc++.h>
using namespace std;


/*
    数位DP
    模版学习：https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/2595149/shu-wei-dp-shang-xia-jie-mo-ban-fu-ti-da-h6ci/
    
    Problems：
    LC3490 https://leetcode.cn/problems/count-beautiful-numbers/
    LC2999 https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/2595149/shu-wei-dp-shang-xia-jie-mo-ban-fu-ti-da-h6ci/
*/
//LC3490. https://leetcode.cn/problems/count-beautiful-numbers/
class Solution {
    public:
        int beautifulNumbers(int l, int r) {
            string low = to_string(l), high = to_string(r);
            int n = high.size();
            int diff = n - low.size(); //这样写无需加前导0
            unordered_map<long long, int> memo;
    
            auto dfs = [&](this auto&& dfs, int i, int m, int s, bool limitLow, bool limitHigh) -> int {
                if(i == n) {
                    return s && m % s == 0;
                }
    
                long long mask = (long long) m << 32 | i << 16 | s;
                if(!limitLow && !limitHigh && memo.contains(mask)) {
                    return memo[mask];
                }
    
                int lo = limitLow && i >= diff ? low[i - diff] - '0': 0;
                int hi = limitHigh ? high[i] - '0': 9;
    
                int res = 0;
                int d = lo;
                if(limitLow && i < diff) { //
                    res = dfs(i + 1, 1, 0, true, false);  //什么都没填
                    d = 1; 
                }
                for(; d <= hi; d ++ ) {
                    res += dfs(i + 1, m * d, s + d, limitLow && d == lo, limitHigh && d == hi);
                }
                if(!limitLow && !limitHigh) {
                    memo[mask] = res;
                }
                return res;
            };
    
            return dfs(0, 1, 0, true, true);
        }
    };


/* ---------------------------------------------------------------------------------------------------------------------- */

