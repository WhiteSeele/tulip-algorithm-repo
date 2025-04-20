#include<bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> mat(n);

    for(int i = 0; i < n; i ++ ) {
        std::cin >> mat[i];
    }

    int r = 0, c = 0;
    for(int i = 0; i < n; i ++ ) {
        bool sum = 0;
        for(int j = 0; j < m; j ++ ) {
            sum ^= (mat[i][j] - '0');
        }
        r += sum;
    }

    for(int j = 0; j < m; j ++ ) {
        bool sum = 0;
        for(int i = 0; i < n; i ++ ) {
            sum ^= (mat[i][j] - '0');
        }
        c += sum;
    }

    std::cout << std::max(r, c) << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while(t -- ) {
        solve();
    }
    return 0;
}