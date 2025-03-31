#include<bits/stdc++.h>
using namespace std;



/*-------------------------------------------划分型 DP------------------------------------------------------------------*/
/*
    划分型 DP
    1. 判定能否划分
    状态定义：f[i] 表示长为 i 的前缀 a[:i] 能否划分
    枚举最后一个子数组的左端点 L，从 f[L] 转移到 f[i]，并考虑 a[L:i] 是否符合要求
    例题：
    LC139 https://leetcode.cn/problems/word-break/description/
    LC2369 https://leetcode.cn/problems/check-if-there-is-a-valid-partition-for-the-array/description/

    2. 最优划分
    计算最少 / 最多可以划分出多少段，最优划分得分等
    状态定义：f[i] 表示长为 i 的前缀 a[:i] 在约束条件下分割出的最少（最多）子数组个数（分割方案数）
    枚举最后一个子数组的左端点 L，从 f[L] 转移到 f[i]，并考虑 a[L:i] 对最优解的影响
    例题：
    LC132 https://leetcode.cn/problems/palindrome-partitioning-ii/description/
    LC2430 https://leetcode.cn/problems/maximum-deletions-on-a-string/

    3. 约束划分个数
    将数组分成（至少 / 恰好 / 至多）k 个连续子数组，计算与这些子数组有关的最优值
    状态定义：f[i][j] 表示将长为 j 的前缀 a[:j] 分成 i 个连续子数组所得到的最优解
    枚举最后一个子数组的左端点 L ，从 f[i - 1][L] 转移到 f[i][j]，并考虑 a[L:j] 对子数组的影响
    例题：
    LC410 https://leetcode.cn/problems/split-array-largest-sum/
    LC1745 https://leetcode.cn/problems/palindrome-partitioning-iv/
    LC3505 https://leetcode.cn/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/description/
*/




/* ---------------------------------------------数位DP------------------------------------------------------------------*/
/*
    数位DP
    模版v1.0：https://www.bilibili.com/video/BV1rS4y1s721/?t=19m36s&vd_source=23e0bd55bd02390a9b07e67223434fa4
    模版v2.0：https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/2595149/shu-wei-dp-shang-xia-jie-mo-ban-fu-ti-da-h6ci/
    
    Problems：
    LC3490 https://leetcode.cn/problems/count-beautiful-numbers/
    LC2999 https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/2595149/shu-wei-dp-shang-xia-jie-mo-ban-fu-ti-da-h6ci/
    LC2827 https://leetcode.cn/problems/number-of-beautiful-integers-in-the-range/
    LC2376 https://leetcode.cn/problems/count-special-integers/description/
*/

//模板题: LC2999 https://leetcode.cn/problems/count-the-number-of-powerful-integers/
class Solution {
    public:
        long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
            auto low = to_string(start), high = to_string(finish);
    
            int n = high.length();
            int diff_hl = n - low.length();
            vector<long long> memo(n, -1);
            
            //数位 DP v2.1  ->  数位DP v2.0 的优化：对 isNum 进行优化
            auto dfs = [&](this auto&& dfs, int i, bool limitLow, bool limitHigh) -> long long {
                if(i == n) {
                    return 1;
                }
                if(!limitLow && !limitHigh && memo[i] != -1) {
                    return memo[i];
                }
    
                //枚举第 i 位填什么
                //如果对数位有其他约束，只能在下面的 for 循环中做约束，此处尽量不要修改
                int lo = limitLow && i >= diff_hl ? low[i - diff_hl] - '0': 0;
                int hi = limitHigh ? high[i] - '0': 9;
    
                int diff_s = n - s.length();
                long long res = 0;
                int d = lo;
                if(limitLow && i < diff_hl) {
                    res += dfs(i + 1, true, false);
                    d = 1;
                }
    
                if(i < diff_s) {
                    for(; d <= min(hi, limit); d ++ ) {
                        res += dfs(i + 1, limitLow && d == lo, limitHigh && d == hi);
                    }
                } else {
                    int x = s[i - diff_s] - '0';
                    if(lo <= x && x <= min(hi, limit)) {
                        res = dfs(i + 1, limitLow && x == lo, limitHigh && x == hi);
                    }
                }
    
                if(!limitLow && !limitHigh) {
                    memo[i] = res;
                }
                return res;
            };
    
            return dfs(0, true, true);
        }
    };

//模板题： LC3490. https://leetcode.cn/problems/count-beautiful-numbers/
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



/* -----------------------------------------------前后缀分解------------------------------------------------------------------- */
/*
    前后缀分解: 考虑以nums[i]为分界线，nums[0:i-1] 和 nums[i+1:] 的情况
    LC2680[前后缀分解 + 贪心] https://leetcode.cn/problems/maximum-or/description/
    LC2012 https://leetcode.cn/problems/sum-of-beauty-in-the-array/
    LC2712 https://leetcode.cn/problems/minimum-cost-to-make-all-characters-equal/?envType=daily-question&envId=2025-03-27
*/

