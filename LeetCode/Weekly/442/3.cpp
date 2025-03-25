#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/find-the-minimum-amount-of-time-to-brew-potions/?slug=minimum-operations-to-make-array-elements-zero&region=local_v2
class Solution {
    public:
        long long minTime(vector<int>& skill, vector<int>& mana) {
            int n = skill.size(), m = mana.size();

            vector<long long> last(n);

            for(int m: mana) {
                long long t = 0;

                //按题目模拟一遍，将等待的时间算在里面算出完成当前药水的时间
                for(int i = 0; i < n; i ++ ) {
                    t = max(last[i], t) + skill[i] * m;
                }

                //倒推，从药水的完成时间来计算实际应该开始的时间
                for(int i = n - 1; i >= 0; i -- ) {
                    last[i] = t;
                    t -= skill[i] * m;
                }
            }

            return last[n - 1];
        }
    };