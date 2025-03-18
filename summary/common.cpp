#include<bits/stdc++.h>
using namespace std;

/*----------------------------------------------------------------------------*/
/*
    滑动窗口
    用双指针维护一个窗口[l,r]，移动 r 使得窗口满足一定条件后再移动左指针缩小窗口指导条件不再满足，更新答案。时间复杂度
    通常为O(n)，因为一个元素最多被访问两次。
*/

//定长滑动窗口
//学习视频: https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/solutions/2809359/tao-lu-jiao-ni-jie-jue-ding-chang-hua-ch-fzfo/
/*
    LC2841 https://leetcode.cn/problems/maximum-sum-of-almost-unique-subarray/
    LC2156 https://leetcode.cn/problems/find-substring-with-given-hash-value/
    LC2653 https://leetcode.cn/problems/sliding-subarray-beauty/
    LC1297 https://leetcode.cn/problems/maximum-number-of-occurrences-of-a-substring/
*/

//不定长滑动窗口
/*
    求最长/最大
    一般题目都有 至多 的要求
    LC3 https://leetcode.cn/problems/longest-substring-without-repeating-characters/
    LC1658 https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/
    LC2106 https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/
    LC2781 https://leetcode.cn/problems/length-of-the-longest-valid-substring/

    求最短/最小
    一般题目都有 至少 的要求
    LC76 https://leetcode.cn/problems/minimum-window-substring/
    LC1234 https://leetcode.cn/problems/replace-the-substring-for-balanced-string/

    求子数组个数

    越长越合法：更新答案方式为 ans += left
    滑动窗口内层窗口结束时右端点固定在 right，左端点在 0, 1, 2, ..., left - 1的所有子数组(子串)都是合法的，
    一共有 left 个。
    LC1358 https://leetcode.cn/problems/number-of-substrings-containing-all-three-characters/
    LC2962 https://leetcode.cn/problems/count-subarrays-where-max-element-appears-at-least-k-times/
    LC3325 https://leetcode.cn/problems/count-substrings-with-k-frequency-characters-i/

    越短越合法：更新答案方式为 ans += right - left + 1. 
    滑动窗口的内层循环结束时右端点固定在 right，左端点在left, left + 1, ..., right 的所有子数组都是合法的，
    一共有 right - left + 1 个
    LC2302 https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/
    LC2762 https://leetcode.cn/problems/continuous-subarrays/

    恰好型滑动窗口
    例如：计算有多少个元素和恰好等于 k 的子数组，将问题拆分为：
     - 计算有多少个元素和 >= k 的子数组f(k)
     - 计算有多少个元素和 >= k + 1 的子数组f(k + 1)
     答案为 f(k) - f(k + 1)。实现时 f 可封装为一个滑窗实现。也可以拆分为 <= k 和 <= k - 1
     恰好型滑动窗口可以拆分为两个【至少】型滑窗或者两个【至多】型滑窗问题

     Q: 为什么不直接将条件固定为 == k？
     A: 恰好等于 k 的左指针是一个在数组中间的范围，需要用两个左指针表示。例如 001000101100，恰好有3个1的窗口
        左指针是呢范围为[3, 6](下标从0开始)。可以看成有 >= 3 个 1 的滑窗问题和有 >= 4 个的滑窗问题答案的差。
    LC3306 https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
    LC1248 https://leetcode.cn/problems/count-number-of-nice-subarrays/
    LC930 https://leetcode.cn/problems/binary-subarrays-with-sum/
*/

/* ----------------------------------------------------------------------------------------------------------------------- */