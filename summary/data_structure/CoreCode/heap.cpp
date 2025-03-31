//堆相关
#include<bits/stdc++.h>
using namespace std;

//懒删除堆
/*
    堆有大量插入和删除操作时，每一次删除操作都去遍历一遍堆速度太慢了。
    在删除的时候可以不去在堆中实际删除这个数，而是记录删除键为 x 的操作，并不去执行删除操作。等到
    出堆/查看栈顶 时才真正执行删除操作。
    具体而言：
    1. 记录下每个元素剩余要删除的次数lazyRemove[x]
    2. 删除 remove(x): lazyRemove[x] ++ 
    3. 入堆 push(x): lazyRemove[x] == 0 正常入堆，否则 lazyRemove[x] -- 
    4. 出堆 pop(): 如果 lazyRemove[top()] > 0，弹出堆顶，重复直到lazyRemove[top()] == 0。
        最后弹出堆顶元素
    
    需要额外变量 sz 来记录堆的大小
*/
//模板
template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> lazyRemove;       //元素需要删除的次数
    size_t sz = 0;

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

    void remove(T x) {
        lazyRemove[x] ++ ;
        sz -- ;
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
    }

    //push(x) 后 pop()
    T push_pop(T x) {
        applyRemove();
        pq.push(x);
        x = pq.top();
        pq.pop();
        return x;
    }

};
/*
    例题：
    LC480[LC295 + 定长滑动窗口 + 懒删除堆] https://leetcode.cn/problems/sliding-window-median/description/
    LC3505 https://leetcode.cn/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/description/
*/

//对顶堆
/*
    LC295 https://leetcode.cn/problems/find-median-from-data-stream/description/
    中位数：
    class MedianFinder {
        //规定：0 <= left.size() - right.size() <= 1
        priority_queue<int, vector<int>, std::less<>> left; //最大堆
        priority_queue<int, vector<int>, std::greater<>> right;  //最小堆
    public:
        MedianFinder() { }
    
        void addNum(int num) {
            if(left.size() == right.size()) {
                right.push(num);
                left.push(right.top());
                right.pop();
            } else {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    
        double findMedian() {
            if(left.size() == right.size()) {
                return (left.top() + right.top()) / 2.0;
            }
            return left.top();
        }
    };

    LC480[结合懒删除堆] https://leetcode.cn/problems/sliding-window-median/description/
*/