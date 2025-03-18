/*
    总结一些 ACM 模式下的线段树(无区间更新)模版题
*/

//AcWing1275. https://www.acwing.com/activity/content/problem/content/1607/
#include<bits/stdc++.h>
const int N = 200010;

struct Node{
    int l, r;
    int maxv;
}tr[4 * N];

int m, n, a, p;
int b[N];

void pushup(int u){
    tr[u].maxv = std::max(tr[u << 1].maxv, tr[u << 1 | 1].maxv);
}

void build(int u, int l, int r){
    if(l == r) tr[u] = {l, r, b[r]};   // l == r!!!
    else{
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int x, int v){
    if(tr[u].l == tr[u].r) {
        tr[u].maxv = v;
        b[x] = v;
    }
    else{
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

int query(int u, int l, int r){
    if(l <= tr[u].l && tr[u].r <= r) return tr[u].maxv;
    int mid = tr[u].l + tr[u].r >> 1;
    int res = 0;
    if(l <= mid) res = std::max(res, query(u << 1, l, r));
    if(r > mid) res = std::max(res, query(u << 1 | 1, l, r));
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> m >> p;

    build(1, 1, N - 1);

    while(m -- ){
        std::string op;
        std::cin >> op;
        if(op == "Q"){
            int l;
            std::cin >> l;
            a = query(1, n - l + 1, n);
            std::cout << a << '\n';
        }
        if(op == "A"){
            int t;
            std::cin >> t;
            modify(1, ++ n, ((long long)t + a) % p);
        }
    }

    return 0;
}