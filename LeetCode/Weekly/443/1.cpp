#include<bits/stdc++.h>
using namespace std;


//https://leetcode.cn/problems/minimum-cost-to-reach-every-position/description/
class Solution {
    public:
        vector<int> minCosts(vector<int>& cost) {
            int n = cost.size();
    
            vector<int> ans(n);
            int minV = INT_MAX / 4;
            for(int i = 0; i < n; i ++ ) {
                minV = min(minV, cost[i]);
                ans[i] = minV;
            }
            return ans;
        }
    };