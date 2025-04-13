#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/biweekly-contest-154/problems/number-of-unique-xor-triplets-ii/description/?slug=number-of-unique-xor-triplets-ii&region=local_v2

//【两数之和】
class Solution {
    public:
        int uniqueXorTriplets(vector<int>& nums) {
            int n = nums.size();
    
            unordered_set<int> vis;
            for(int i = 0; i < n; i ++ ) {
                for(int j = i + 1; j < n; j ++ ) {
                    int res = nums[i] ^ nums[j];
                    vis.insert(res);
                }
            }
            vis.insert(0);
            unordered_set<int> st;
            for(int x: vis) {
                for(int k = 0; k < n; k ++ ) {
                    st.insert(x ^ nums[k]);
                }
            }
            return st.size();
        }
    };