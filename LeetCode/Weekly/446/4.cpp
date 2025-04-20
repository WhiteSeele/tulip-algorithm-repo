#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-446/problems/find-x-value-of-array-ii/description/

//线段树

class SegmentTree {
    //线段树节点存储：区间[l,r]的积的余数；左端点为l，右端点为l，l + 1，l + 2，...，r的元素积模 k
    //余数为 x 的子数组个数
    using T = pair<int, array<int, 5>>;
    int n;
    int k;
    vector<T> tree;

    // 合并两个 val
    T merge_val(T a, T b) const {
        auto [leftMul, cnt] = a;
        for(int rx = 0; rx < k; rx ++ ) {
            cnt[leftMul * rx % k] += b.second[rx];
        }
        return make_pair(leftMul * b.first % k, cnt);
    }

    T new_val(int val) const {
        int mul = val % k;
        array<int, 5> cnt{};
        cnt[mul] = 1;
        return make_pair(mul, cnt);
    }

    // 合并左右儿子的 val 到当前节点的 val
    void maintain(int node) {
        tree[node] = merge_val(tree[node * 2], tree[node * 2 + 1]);
    }

    // 用 a 初始化线段树
    // 时间复杂度 O(n)
    void build(const vector<int>& a, int node, int l, int r) {
        if (l == r) { // 叶子
            tree[node] = new_val(a[l]); // 初始化叶节点的值
            return;
        }
        int m = (l + r) / 2;
        build(a, node * 2, l, m); // 初始化左子树
        build(a, node * 2 + 1, m + 1, r); // 初始化右子树
        maintain(node);
    }

    void update(int node, int l, int r, int i, int val) {
        if (l == r) { // 叶子（到达目标）
            // 如果想直接替换的话，可以写 tree[node] = val
            tree[node] = new_val(val);
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) {  // i 在左子树
            update(node * 2, l, m, i, val);
        } else {  // i 在右子树
            update(node * 2 + 1, m + 1, r, i, val);
        }
        maintain(node);
    }

    T query(int node, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) { // 当前子树完全在 [ql, qr] 内
            return tree[node];
        }
        int m = (l + r) / 2;
        if (qr <= m) {  // [ql, qr] 在左子树
            return query(node * 2, l, m, ql, qr);
        }
        if (ql > m) {  // [ql, qr] 在右子树
            return query(node * 2 + 1, m + 1, r, ql, qr);
        }
        T l_res = query(node * 2, l, m, ql, qr);
        T r_res = query(node * 2 + 1, m + 1, r, ql, qr);
        return merge_val(l_res, r_res);
    }

public:
    // 线段树维护数组 a
    SegmentTree(const vector<int>& a, int k) : k(k), n(a.size()), tree(2 << bit_width(a.size() - 1)) {
        build(a, 1, 0, n - 1);
    }

    // 更新 a[i] 为 merge_val(a[i], val)
    // 时间复杂度 O(log n)
    void update(int i, int val) {
        update(1, 0, n - 1, i, val);
    }

    // 返回用 merge_val 合并所有 a[i] 的计算结果，其中 i 在闭区间 [ql, qr] 中
    // 时间复杂度 O(log n)
    T query(int ql, int qr) const {
        return query(1, 0, n - 1, ql, qr);
    }

    // 获取 a[i] 的值
    // 时间复杂度 O(log n)
    T get(int i) const {
        return query(1, 0, n - 1, i, i);
    }
};
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        SegmentTree t(nums, k);
        int n = nums.size();
        vector<int> ans;

        for(auto& q: queries) {
            t.update(q[0], q[1]);
            auto [_, cnt] = t.query(q[2], n - 1);
            ans.emplace_back(cnt[q[3]]);
        }

        return ans;
    }
};