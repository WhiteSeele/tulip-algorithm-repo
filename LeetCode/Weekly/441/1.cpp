#include<bits/stdc++.h>
using namespace std;

/*
    https://leetcode.cn/problems/maximum-unique-subarray-sum-after-deletion/description/
    所有非负的整数去重的和
    如果全部为负数，则答案为负数的最大值。
*/

class Solution {
    public:
        int maxSum(vector<int>& nums) {
            unordered_set<int> st;
    
            int nemax = INT_MIN / 4;
            int s = 0;
            for(int x: nums) {
                if(x >= 0 && !st.contains(x)) {
                    s += x;
                    st.insert(x);
                }
                else nemax = max(nemax, x);
            }
    
            return st.size() > 0 ? s: nemax;
        }
    };