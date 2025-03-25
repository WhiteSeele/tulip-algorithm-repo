#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/properties-graph/?slug=minimum-operations-to-make-array-elements-zero&region=local_v2
class Solution {
    public:
        int numberOfComponents(vector<vector<int>>& properties, int k) {
            int n = properties.size(), m = properties[0].size();
            
            vector<int> pa(n);
            for(int i = 0; i < n; i ++ ) {
                pa[i] = i;
            }
    
            auto find = [&](this auto&& find, int i) -> int {
                if(i == pa[i]) return pa[i];
                pa[i] = find(pa[i]);
                return pa[i];
            };
    
            for(int i = 0; i < n; i ++ ) {
                for(int j = i + 1; j < n; j ++ ) {
                    auto& p1 = properties[i];
                    auto& p2 = properties[j];
                    vector<int> s1(101);
                    for(int k = 0; k < m; k ++ ) {
                        s1[p1[k]] ++ ;
                    }
                    vector<int> s2(101);
                    int cnt = 0;
                    for(int k = 0; k < m; k ++ ) {
                        if(s1[p2[k]] && !s2[p2[k]]) {
                            cnt ++ ;
                            s2[p2[k]] ++ ;
                        }
                    }
                    if(cnt >= k) {
                        int pi = find(i), pj = find(j);
                        pa[pi] = pj;
                    }
                }
            }
    
            int ans = 0;
            for(int i = 0; i < n; i ++ ) {
                if(pa[i] == i) ans ++ ;
            }
    
            return ans;
        }
    };