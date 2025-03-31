/* 图论的相关算法 */

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