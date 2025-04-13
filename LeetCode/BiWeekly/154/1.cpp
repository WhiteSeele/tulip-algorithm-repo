#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/minimum-operations-to-make-array-sum-divisible-by-k/
class Solution {
    public:
        int minOperations(vector<int>& nums, int k) {
            int sum = std::reduce(nums.begin(), nums.end());
            
            int kk = sum / k;
            return sum - kk * k;
        }
    };