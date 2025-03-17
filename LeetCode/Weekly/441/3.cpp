#include<bits/stdc++.h>
using namespace std;

/*
    https://leetcode.cn/problems/zero-array-transformation-iv/description/
    0-1背包变体
    nums很小只有10个，根据题意各元素之间相互独立。
    对于每一个nums[i]而言，题目可以看成是从一个数的集合中选出一个子集使得子集的和等于nums[i]。这是一个典型的 0-1 背包问题。
    一共有nums.length个0-1背包问题。遍历queries，遍历的过程中计算0-1背包问题。遍历到第 k 个时如果全部变为0则返回 k + 1.
    特判全为0的情况。
*/

class Solution {
    public:
        int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
            if(ranges::all_of(nums, [](int x) {return x == 0;})) {
                return 0;
            }
            int n = nums.size();
    
            vector<vector<int>> f(n);
            for(int i = 0; i < n; i ++ ) {
                f[i].resize(nums[i] + 1);
                f[i][0] = 1;
            }
    
            for(int k = 0; k < queries.size(); k ++ ) {
                int l = queries[k][0];
                int r = queries[k][1];
                int v = queries[k][2];
                for(int i = l; i <= r; i ++ ) {
                    for(int j = nums[i]; j >= v; j -- ) {
                        f[i][j] = f[i][j] | f[i][j - v];
                    }
                }
                bool ok = true;
                for(auto& sf: f) {
                    if(!sf.back()) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    return k + 1;
                }
            }
            return -1;
        }
};