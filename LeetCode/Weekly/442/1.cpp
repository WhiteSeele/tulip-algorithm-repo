#include<bits/stdc++.h>
using namespace std;


//https://leetcode.cn/problems/maximum-containers-on-a-ship/description/?slug=minimum-operations-to-make-array-elements-zero&region=local_v2
class Solution {
    public:
        int maxContainers(int n, int w, int maxWeight) {
            return min(n * n, maxWeight / w);
        }
    };