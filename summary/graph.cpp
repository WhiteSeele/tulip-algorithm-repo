#include<bits/stdc++.h>
using namespace std;
/* 图论的相关算法 */


/*
    树上倍增算法:
    fa[i, j] 表示从 i 结点出发，向上跳 2 ^ j 步所抵达的节点编号
    j = 0, fa[i, 0] = i的父节点
    j > 0, i 向上跳 2 ^ (i - 1) 步后再跳 2 ^ (i - 1) 步就可以跳到 2 ^ i 的位置，所以有：
        fa[i, j] = fa[fa[i, j - 1], j - 1]
    
    主体思想: 二进制拆分
    
    LCA（最近公共祖先）:
    https://www.acwing.com/activity/content/code/content/6937075/
    https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/solutions/2305895/mo-ban-jiang-jie-shu-shang-bei-zeng-suan-v3rw/
    例题：
    LC1483 https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/description/
    
*/
//树上倍增模板：
class TreeAncestor {
    vector<vector<int>> fa;
    const int M = 16;
public:
    TreeAncestor(int n, vector<int>& parent) {
        vector<vector<int>> f(n, vector<int>(M, -1));
        for(int i = 1; i < n; i ++ ) {
            f[i][0] = parent[i];
        }

        for(int i = 1; i < M; i ++ ) {
            for(int u = 1; u < n; u ++ ) {
                if(int p = f[u][i - 1]; p != -1){
                    f[u][i] = f[p][i - 1];
                }
            }
        }
        fa = move(f);
    }
    
    int getKthAncestor(int node, int k) {
        for(; node != -1 && k; k &= (k - 1)) {
            node = fa[node][__builtin_ctz(k)];  //_builtin_ctz(k): 返回 k 的低位连续0的个数
        }
        return node;
    }
};

//二叉树的最近公共祖先
/*
    LC236 https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
    给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
    满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

    分类讨论：
    递归寻找 p，q
    对于当前结点 node：
        如果 node == p 或 node == q，直接返回当前结点，不需要继续向下找（最近公共祖先就是当前节点）
        如果 node 的左子树中找到 p，q，直接返回左子树的结果
        如果 node 的右子树中找到 p, q，直接返回右子树的结果
        如果 p，q 分别在 node 的左、右子树中，那么 node 就是最近公共祖先，返回 node
    
    函数 lowestCommonAncestor 的返回值如何定义？
    函数的返回值对于最外层调用者来说返回的是p，q的最近公共祖先，但是在递归过程中不一定是最近公共祖先
    可能是空结点（子树内没有任何有用的信息，可以暗示p，q都不在当前子树），节点 p 或节点 q（可能是最近
    公共祖先，也可能是用来辅助判断节点是否为最近公共祖先）
*/
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || root == p || root == q) {
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root -> left, p, q);
        TreeNode* right = lowestCommonAncestor(root -> right, p, q);

        if(left && right) {
            return root;
        }

        return left ? left : right;
    }
};

/*
    相似习题：
    LC235 https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
    LC1123. https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/description/?envType=daily-question&envId=2025-04-04
*/


/*-------------------------------------拓扑排序-------------------------------------------------------------*/
/*
    拓扑排序：对有向图（DAG）上的节点进行排序：
    在一个 DAG（有向无环图） 中，我们将图中的顶点以线性方式进行排序，使得对于任何的顶点 u 到 v 的有向边 (u,v), 都可以有 u 在 v 的前面。
    bool topSort(){
        std::queue<int> q;
        for(int i = 1; i <= n; i ++ ){
            if(!d[i]) q.push(i);
        }

        while(!q.empty()){
            auto tt = q.front();
            q.pop();
            ts.push_back(tt);

            for(auto xx : g[tt]){
                if(-- d[xx] == 0) q.push(xx);
            }
        }

        return ts.size() == n;
    }

    例题：
    LC2360 https://leetcode.cn/problems/longest-cycle-in-a-graph/description/?envType=daily-question&envId=2025-03-29
*/