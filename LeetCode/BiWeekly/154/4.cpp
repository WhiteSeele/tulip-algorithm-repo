#include<bits/stdc++.h>
using namespace std;


//https://leetcode.cn/problems/shortest-path-in-a-weighted-tree/description/
/*
    - 差分树状数组
    - DFS 序 + 时间戳
*/
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    //下标从 1 到 n
    FenwickTree(int n): tree(n + 1) {}

    int lowbit(int x) const { return x & -x;}
    //a[i] 增加 val
    //1 <= i <= n
    void update(int i, T val) {
        for(; i < tree.size(); i += lowbit(i)) {
            tree[i] += val;
        }
    }

    //求前缀和 a[1] + ... + a[i]
    T pre(int i) const {
        T res = 0;
        for(; i ; i -= lowbit(i)) {
            res += tree[i];
        }
        return res;
    }
};

class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<int>> g(n + 1);

        for(auto& e: edges) {
            g[e[0]].emplace_back(e[1]);
            g[e[1]].emplace_back(e[0]);
        }

        //DFS 序 + 时间戳
        vector<int> in(n + 1), out(n + 1);
        int clock = 0;

        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            in[x] = ++ clock;   //进来的时间
            for(int y: g[x]) {
                if(y != fa) {
                    dfs(y, x);
                }
            }
            out[x] = clock;      //离开的时间
        };
        dfs(1, 0);

        vector<int> weight(n + 1);  //边 x - y 的边权存储在 weight[y] 中
        FenwickTree<int> diff(n);

        auto update = [&](int x, int y, int w) {
            //保证 y 是 x 的儿子
            if(in[x] > in[y]) {
                y = x;
            }
            int d = w - weight[y];  //边权的增量
            weight[y] = w;
            //把子树 y 中的最短路径长度都增加 d （差分树状数组）
            diff.update(in[y], d);
            diff.update(out[y] + 1, -d);
        };
 
        for(auto& e: edges) {
            update(e[0], e[1], e[2]);
        }

        vector<int> ans;
        for(auto& q: queries) {
            if(q[0] == 1) {
                update(q[1], q[2], q[3]);
            } else {
                ans.push_back(diff.pre(in[q[1]]));  //本题是树，最短路就是距离
            }
        }

        return ans;
    }
};