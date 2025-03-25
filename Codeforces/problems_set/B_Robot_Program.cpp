#include<bits/stdc++.h>

typedef long long ll;

void solve() {
    ll n, x, k;
    std::cin >> n >> x >> k;

    std::string ops;
    std::cin >> ops;

    ll ans = 0;
    for(auto& op: ops) {
        if(k <= 0) break;
        if(op == 'L') x -- ;
        if(op == 'R') x ++ ;
        k -- ;
        if(x == 0) {
            ans ++ ;
            break;
        }
    }

    if(!ans) {
        std::cout << ans << '\n';
        return;
    }
    int t = 0, i;
    for(i = 0; i < n; i ++ ) {
        char op = ops[i];
        if(k <= 0) break;
        if(op == 'L') x -- ;
        if(op == 'R') x ++ ;
        t ++ ;
        k -- ;
        if(x == 0) {
            ans ++ ;
            break;
        }
    }
    if(k > 0 && i < n) ans += k / t;
    std::cout << ans << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while(t -- ) {
        solve();
    }
    return 0;
}