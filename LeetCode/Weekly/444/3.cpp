#include<bits/stdc++.h>
using namespace std;


//暴力搜索
/*
    dfs(i, s, m, odd, empty):
    考虑 x = nums[i] 选或不选
    子序列交错和为 s
    子序列乘积为 m
    如果选 x，是 + x 还是 - x
    子序列是否为空（排除一直没选的情况）

    分类讨论：
        不选 x：递归到 dfs(i + 1, s, m, odd, empty)
        选 x：递归到 dfs(i + 1, s', min(m * x, limit + 1), !odd, false)
    
    递归终点: i == n && empty == false && s == k && m <= limit，m 更新答案
    入口: dfs(0, 0, 1, false, true);

    哈希表记录访问过的状态，避免重复访问
*/
class Solution {
    public:
        int maxProduct(vector<int>& nums, int k, int limit) {
            int totSum = std::reduce(nums.begin(), nums.end());
            if(totSum < abs(k)) {
                return -1;
            }
    
            int n = nums.size(), ans = -1;
            unordered_set<long long> vis;
    
            auto dfs = [&](this auto&& dfs, int i, int s, int m, bool odd, bool empty){
                if(ans == limit) {
                    return;
                }
    
                if(i == n) {
                    if(s == k && m <= limit && !empty) {
                        ans = max(ans, m);
                    }
                }

                long long mask = (long long) i << 32 | (s + totSum) << 20 | m << 5 | odd << 2 | empty;   // s 有可能为负数，需要做偏移
                if(!vis.insert(mask).second) {
                    return;
                }

                //不选
                dfs(i + 1, s, m, odd, empty);
                int x = nums[i];
                //选
                dfs(i + 1, s + (odd ? -x: x), min(m * x, limit + 1), !odd, false);
            };
    
            dfs(0, 0, 1, false, true);
            return ans;
        }
    };