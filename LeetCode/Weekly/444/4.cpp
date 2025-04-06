#include<bits/stdc++.h>
using namespace std;

/*
    有序集合 + 模拟
    分析题目操作可知，操作序列唯一，因此直接模拟，关键在于使用数据结构降低复杂度。

    设相邻元素对(x, y)，算出共有 dec 个相邻元素对满足 x > y
    目标：通过操作，使得所有相邻元素对都是 x <= y, 即使得 dec == 0
    第一个有序集合：维护(相邻元素和 s, 左侧元素下标)
    第二个有序集合：维护剩余的下标

    用和替换这对元素可以理解为: 设(i, nxt) 为一个相邻数对，用 nums[i] + nums[nxt] 替换相当于把
    nums[i] 增加 nums[nxt]，并删除 nxt 处的元素。

    涉及到相邻元素的大小关系，因此还需要考虑 i 的上一个元素和下下一个元素，分别设为 pre 和 nxt
    接下来就是考虑 pre, i, nxt, nxt2 之间在操作过程中的大小关系来增减 dec 
    循环结束条件: dec == 0
*/

class Solution {
    public:
        int minimumPairRemoval(vector<int>& nums) {
            int n = nums.size();
            set<pair<long long, int>> sumId;
            set<int> idx;
    
            int dec = 0, ans = 0;
    
            for (int i = 0; i + 1 < n; i++) {
                int x = nums[i], y = nums[i + 1];
                if (x > y) {
                    dec++;
                }
                sumId.insert({x + y, i});
            }
            for (int i = 0; i < n; i++) {
                idx.insert(i);
            }
    
            vector<long long> arr(nums.begin(), nums.end());
            while (dec) {
                ans++;
                // 删除相邻元素最小和的一对
                auto [s, i] = *sumId.begin();
                sumId.erase(sumId.begin());
    
                // 当前元素，下一个数
                auto it = idx.lower_bound(i);
                auto nxtIt = next(it);
                int nxt = *nxtIt;
    
                // nxt 被删除
                dec -= arr[i] > arr[nxt];
    
                // 前一个元素，当前元素
                if (it != idx.begin()) {
                    int pre = *prev(it);
                    dec -= arr[pre] > arr[i];   //旧数据
                    dec += arr[pre] > s;        //新数据
                    //注意这里要先删除再插入，先插入的话两者有可能相等导致插入失败，而元素被错误删除
                    sumId.erase({arr[pre] + arr[i], pre});
                    sumId.emplace(arr[pre] + s, pre);
                }
    
                auto nxt2It = next(nxtIt);
                // 下一个元素，下下个元素
                if (nxt2It != idx.end()) {
                    int nxt2 = *nxt2It;
                    dec -= arr[nxt] > arr[nxt2];   //旧数据
                    dec += s > arr[nxt2];          //新数据
                    sumId.erase({arr[nxt] + arr[nxt2], nxt});
                    sumId.emplace(s + arr[nxt2], i);
                }
    
                arr[i] = s;
                idx.erase(nxt);
            }
    
            return ans;
        }
    };