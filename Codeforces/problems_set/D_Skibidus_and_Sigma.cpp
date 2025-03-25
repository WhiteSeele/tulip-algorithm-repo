#include<bits/stdc++.h>

typedef long long ll;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector arrs(n, std::vector<int>(m));

    for(int i = 0; i < n; i ++ ) {
        for(int j = 0; j < m; j ++ ) {
            std::cin >> arrs[i][j];
        }
    }

    std::vector sums(n, std::vector<ll>(m + 1));
    for(int i = 0; i < n; i ++ ) {
        for(int j = 0; j < m; j ++ ) {
            sums[i][j + 1] = sums[i][j] + arrs[i][j];
        }
    }

    std::sort(sums.begin(), sums.end(), [m](const std::vector<ll>& a1, const std::vector<ll>& a2) {
        int id = m;

        while(id > 0 && a1[id] == a2[id]) id -- ;
        return a1[id] > a2[id];
    });
    
    ll ans = 0;
    ll tmp = 0, t0 = 0;
    for(int i = 0; i < n; i ++ ) {
        tmp = 0;
        for(int j = 0; j <= m; j ++ ) {
            tmp += sums[i][j];
        }
        tmp += m * t0;
        ans += tmp;
        t0 += sums[i][m];
    }
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