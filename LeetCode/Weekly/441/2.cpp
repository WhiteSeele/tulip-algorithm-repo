#include<bits/stdc++.h>
using namespace std;

/*
    https://leetcode.cn/problems/closest-equal-element-queries/description/
    排序 + 二分
*/
class Solution {
    public:
        vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
            int n = nums.size();
    
            unordered_map<int, vector<int>> mp;
            for(int i = 0; i < n; i ++ ) {
                mp[nums[i]].emplace_back(i);
            }
    
            vector<int> ans;
    
            for(auto& q: queries) {
                int val = nums[q];
                auto& idv = mp[val];
    
                int pos = lower_bound(idv.begin(), idv.end(), q) - idv.begin();
                int m = idv.size();
                int pre = idv[((pos - 1) % m + m) % m];
                int pro = idv[(pos + 1) % m];
    
                int d1 = min(abs(pre - q), n - abs(pre - q));
                int d2 = min(abs(pro - q), n - abs(pro - q));
    
                ans.emplace_back((min(d1, d2) == 0)? -1: min(d1, d2));
            }
            return ans;
        }
    };