#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/biweekly-contest-154/problems/number-of-unique-xor-triplets-i/?slug=number-of-unique-xor-triplets-i&region=local_v2

//位运算（异或的最大值）
class Solution {
    public:
        int uniqueXorTriplets(vector<int>& nums) {
            int n = nums.size();
            if(n < 3) return n;
    
            int p = __lg(n);
            return 1 << (p + 1);
        }
    };