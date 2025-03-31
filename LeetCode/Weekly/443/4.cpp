#include<bits/stdc++.h>
using namespace std;

//https://leetcode.cn/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/
/*
    知识点相关习题：
    LC462[中位数贪心]. https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/description/
    LC480[滑动窗口中位数]. https://leetcode.cn/problems/sliding-window-median/description/
    LC2602[距离和]. https://leetcode.cn/problems/minimum-operations-to-make-all-array-elements-equal/description/
    划分型DP
*/

/*
    f[i][j]: [0:j - 1] 中包含 i 个长为 x 的子数组的最小操作次数
    子数组不包含 nums[j - 1]: 从[0:j-2] 中选择 i 个长为 x 的子数组最小次数f[i][j - 1]
    子数组包含 nums[j - 1]: 子数组左端点为 nums[j - x]，从[0:j-x-1]中选择 i - 1 个子数组
    的最小操作次数加上将子数组全部变为相同的最小操作次数
    f[i][j] = min(f[i][j - 1], f[i - 1][j - x] + dis[j - x])
    dis[k]: 以 k 为左端点长为 x 的子数组全部变为相同的最少操作次数【中位数贪心 + 滑动窗口中位
    数】
*/

/*
    f[i][j]: [0:j - 1] 中包含 i 个长为 x 的子数组的最小操作次数
    子数组不包含 nums[j - 1]: 从[0:j-2] 中选择 i 个长为 x 的子数组最小次数f[i][j - 1]
    子数组包含 nums[j - 1]: 子数组左端点为 nums[j - x]，从[0:j-x-1]中选择 i - 1 个子数组
    的最小操作次数加上将子数组全部变为相同的最小操作次数
    f[i][j] = min(f[i][j - 1], f[i - 1][j - x] + dis[j - x])
    dis[k]: 以 k 为左端点长为 x 的子数组全部变为相同的最少操作次数【中位数贪心 + 滑动窗口中位
    数】
*/
template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> lazyRemove;       //元素需要删除的次数
    size_t sz = 0;

    long long s = 0;

    //正式操作
    void applyRemove() {
        while(!pq.empty() && lazyRemove[pq.top()]) {
            lazyRemove[pq.top()] -- ;
            pq.pop();
        }
    }

public:
    size_t size() {
        return sz;
    }

    long long sum() {
        return s;
    }

    void remove(T x) {
        lazyRemove[x] ++ ;
        sz -- ;
        s -= x;
    }

    //查看堆顶
    T top() {
        applyRemove();
        return pq.top();
    }

    T pop() {
        applyRemove();
        sz -- ;
        T x = pq.top();
        s -= x;
        pq.pop();
        return x;
    }

    void push(T x) {
        if(lazyRemove[x] > 0) {
            lazyRemove[x] -- ;
        } else {
            pq.push(x);
        }
        sz ++ ;
        s += x;
    }

    //push(x) 后 pop()
    T push_pop(T x) {
        applyRemove();
        pq.push(x);
        s += x;
        x = pq.top();
        pq.pop();
        s -= x;
        return x;
    }

};

class Solution {
    public:
        //480. 滑动窗口中位数
        //懒删除堆中多维护一个变量表示堆中元素的总和方便计算操作次数
        vector<long long> calculate(const vector<int>& nums, int k) {
            int n = nums.size();
            vector<long long> ret(n);
            LazyHeap<int> left;
            LazyHeap<int, std::greater<int>> right;

            for(int i = 0; i < n; i ++ ) {
                //1. 入堆
                if(left.size() == right.size()) {
                    left.push(right.push_pop(nums[i]));
                } else {
                    right.push(left.push_pop(nums[i]));
                }

                int l = i - k + 1;
                if(l < 0) continue;

                //2. 计算答案
                long long m = left.top();       //直接取左边的就行，操作次数是一样的
                long long v1 = left.size() * m - left.sum();
                long long v2 = right.sum() - m * right.size();
                ret[l] = v1 + v2;

                //3. 出堆
                long long out = nums[l];
                if(out <= left.top()) {
                    left.remove(out);
                    if(left.size() < right.size()) {
                        left.push(right.pop());
                    }
                } else {
                    right.remove(out);
                    if(left.size() > right.size() + 1) {
                        right.push(left.pop());
                    }
                }
            }
            return ret;
        };

        long long minOperations(vector<int>& nums, int x, int k) {
            int n = nums.size();

            vector f(k + 1, vector<long long>(n + 1));
            vector<long long> dis = calculate(nums, x);
            f[0][0] = 0;

            for(int i = 1; i <= k; i ++ ) {
                f[i][i * x - 1] = LLONG_MAX / 3;
                for(int j = i * x; j <= n - (k - i) * x; j ++ ) {
                    f[i][j] = min(f[i][j - 1], f[i - 1][j - x] + dis[j - x]);
                }
            }

            return f[k][n];
        }
    };