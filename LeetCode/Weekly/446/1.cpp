#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-446/problems/calculate-score-after-performing-instructions/?slug=find-x-value-of-array-i&tab=description&region=local_v2
class Solution {
    public:
        long long calculateScore(vector<string>& instructions, vector<int>& values) {
            int n = values.size();
            long long ans = 0;
    
            vector<int> vis(n);
            int i = 0;
            while(i >= 0 && i < n && !vis[i]){
                auto op = instructions[i];
                vis[i] = 1;
                if(op == "add") {
                    ans += (long long)values[i];
                    i ++ ;
                } else {
                    i = i + values[i];
                }
            }
            return ans;
        }
    };