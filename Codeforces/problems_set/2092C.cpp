#include<bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    int odd = 0, even = 0;
    long long sum = 0;
    int mx = 0;
    for(int i = 0; i < n; i ++ ) {
        int a;
        std::cin >> a;
        if(a % 2 == 0) even ++ ;
        else odd ++ ;
        sum += (long long)a;
        mx = std::max(mx, a);
    }

    if(odd && even) std::cout << sum - odd + 1 << '\n';
    else std::cout << mx << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while(t -- ) {
        solve();
    }
    return 0;
}