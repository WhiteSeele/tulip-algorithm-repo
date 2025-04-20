#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-446/problems/make-array-non-decreasing/description/?slug=find-x-value-of-array-i&tab=description&region=local_v2

class Solution {
    public:
        int maximumPossibleSize(vector<int>& nums) {
            int n = nums.size();
    
            stack<int> stk;
    
            for(int i = 0; i < n; i ++ ) {
                if(stk.empty()) {
                    stk.push(nums[i]);
                } else {
                    if(nums[i] >= stk.top()) {
                        stk.push(nums[i]);
                    }
                }
            }
    
            return stk.size();
        }
    };