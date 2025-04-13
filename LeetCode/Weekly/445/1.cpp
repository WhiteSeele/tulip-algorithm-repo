#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-445/problems/find-closest-person/description/?slug=smallest-palindromic-rearrangement-ii&tab=description&region=local_v2

class Solution {
    public:
        int findClosest(int x, int y, int z) {
            int a = abs(x - z);
            int b = abs(y - z);
            if(a == b) return 0;
            if(a > b) return 2;
            return 1;
        }
    };