//2071B
#include<bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    long long tot = 1LL * (n + 1) * n / 2;
    long long stot = std::sqrt(tot);
    if(stot * stot == tot) {
        std::cout << -1 << '\n';
        return;
    }

    for(int i = 1; i <= n; i ++ ) {
        int pre = std::sqrt((long long)i * (i + 1) / 2);
        if(pre * (long long)pre == (long long)i * (i + 1) / 2) {
            std::cout << i + 1 << " " << i << " ";
            i ++ ;
        } else {
            std::cout << i << " ";
        }
    }    
    
    std::cout << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while(t -- ) {
        solve();
    }
    return 0;
}