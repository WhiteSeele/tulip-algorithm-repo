#include<bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);

    for(int i = 0; i < n; i ++ ) {
        std::cin >> a[i];
    }

    int mid = n / 2;
    int r = n;
    std::vector<std::pair<int, int>> ops;
    for(int i = mid; i < n; i ++ ) {
        if(a[i] == 0) {
            ops.emplace_back(mid + 1, n);
            r -= n - mid - 1;
            break;
        }
    }
    for(int i = 0; i < mid; i ++ ) {
        if(a[i] == 0) {
            ops.emplace_back(1, mid);
            r -= mid - 1;
            break;
        }
    }
    ops.emplace_back(1, r);
    std::cout << ops.size() << '\n';
    for(auto& [l, r]: ops) {
        std::cout << l << " " << r << '\n';
    }
}

int main() {
    int t;
    std::cin >> t;
    while(t -- ) {
        solve();
    }
    return 0;
}