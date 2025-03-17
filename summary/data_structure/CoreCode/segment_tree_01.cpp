#include<bits/stdc++.h>
using namespace std;

/*
    线段树（无区间更新）
    327. 区间和的个数 https://leetcode.cn/problems/count-of-range-sum/
*/

class SegmentTree {
    vector<int> ct;
    vector<int> p;

    void maintain(int o) {
        ct[o] = ct[o << 1] + ct[o << 1 | 1];
    }

public:
    SegmentTree(int n) {
        ct.resize(4 * n);
        p.resize(n);
    }

    int query(int o, int l, int r, int pl, int pr) {
        if(pl <= l && r <= pr) return ct[o];

        int m = l + r >> 1;
        int res = 0;
        if(pl <= m) {
            res += query(o << 1, l, m, pl, pr);
        }
        if(pr > m) {
            res += query(o << 1 | 1, m + 1, r, pl, pr);
        }
        return res;
    }

    void modify(int o, int l, int r, int x) {
        if(l == r) {
            p[x] += 1;
            ct[o] = p[x];
            return;
        }

        int m = l + r >> 1;
        if(x <= m) modify(o << 1, l, m, x);
        else modify(o << 1|1, m + 1, r, x);

        maintain(o);
    }
};
