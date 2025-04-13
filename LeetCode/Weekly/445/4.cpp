#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/contest/weekly-contest-445/problems/count-numbers-with-non-decreasing-digits/submissions/621714263/?slug=count-numbers-with-non-decreasing-digits&tab=submissions&tab=621714263&region=local_v2
class Solution {
    public:
        const int MOD = 1e9 + 7;
        pair<string, int> divideDecimalString(const string& num, int b) {
            string quotient;
            int remainder = 0;
            for (char c : num) {
                int digit = c - '0';
                int current = remainder * 10 + digit;
                quotient.push_back((current / b) + '0');
                remainder = current % b;
            }
            size_t start = 0;
            while (start < quotient.size() && quotient[start] == '0') {
                start++;
            }
            if (start == quotient.size()) {
                quotient = "0";
            } else {
                quotient = quotient.substr(start);
            }
            return {quotient, remainder};
        }
    
        string decimalToBase(const string& decimal, int base) {
            if (decimal == "0") {
                return "0";
            }
            vector<int> digits;
            string num = decimal;
            while (num != "0") {
                auto [q, r] = divideDecimalString(num, base);
                digits.push_back(r);
                num = q;
            }
            reverse(digits.begin(), digits.end());
            string res;
            for (int d : digits) {
                res += to_string(d);
            }
            return res.empty() ? "0" : res;
        }
        int countNumbers(string l, string r, int b) {
            string low = decimalToBase(l, b), high = decimalToBase(r, b);
            int n = high.size();
            int diff = n - low.size(); 
            unordered_map<long long, long long> memo;
    
            auto dfs = [&](this auto&& dfs, int i, int prev, bool limitLow,
                           bool limitHigh) -> long long {
                if (i == n) {
                    return 1;
                }
    
                long long mask = (long long)i << 32 | prev;
                if (!limitLow && !limitHigh && memo.contains(mask)) {
                    return memo[mask];
                }
    
                int lo = limitLow && i >= diff ? low[i - diff] - '0' : 0;
                int hi = limitHigh ? high[i] - '0' : b - 1;
    
                long long res = 0;
                int d = lo;
                if (limitLow && i < diff) {                    
                    res = dfs(i + 1, prev, true, false) % MOD;
                    d = 1;
                }
                for (; d <= hi; d++) {
                    if (d >= prev)
                        res += dfs(i + 1, d, limitLow && d == lo,
                                   limitHigh && d == hi) %
                               MOD;
                }
                if (!limitLow && !limitHigh) {
                    memo[mask] = res;
                }
                return res;
            };
    
            return dfs(0, -1, true, true) % MOD;
        }
    };