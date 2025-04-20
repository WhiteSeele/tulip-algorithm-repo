#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-446/problems/find-x-value-of-array-i/description/?slug=find-x-value-of-array-i&tab=description&region=local_v2

//刷表法 + 最大子数组和 DP
class Solution {
    public:
        vector<long long> resultArray(vector<int>& nums, int k) {
            int n = nums.size();
    
            vector<long long> ans(k);
            vector f(n + 1, vector<long long>(k, 0LL));
    
            for(int i = 0; i < n; i ++ ) {
                int v = nums[i];
                f[i + 1][v % k] = 1;
                for(int j = 0; j < k; j ++ ) {
                    f[i + 1][1LL * j * v % k] += f[i][j];   //刷表法
                }
                for(int j = 0; j < k; j ++ ) {
                    ans[j] += f[i + 1][j];
                }
            }
            return ans;
        }
    };