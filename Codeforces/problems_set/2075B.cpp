//2075B
#include <bits/stdc++.h>
#include <ranges>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<long long> arr(n);
    for(int i = 0; i < n; i ++ ) {
        std::cin >> arr[i];
    }
    long long ans = 0;
    if(k > 1) {
        std::ranges::sort(arr, {}, [](auto a) { return -a; });
        ans = std::reduce(arr.begin(), arr.begin() + k + 1, 0LL);
    } else {
        long long m1 = *std::max_element(arr.begin(), arr.end() - 1);
        long long m2 = *std::max_element(arr.begin() + 1, arr.end());
        ans = std::max(m1 + arr.back(), m2 + arr[0]);
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