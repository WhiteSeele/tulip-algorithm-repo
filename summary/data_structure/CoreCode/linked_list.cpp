//链表类型数据结构的相关习题

#include<bits/stdc++.h>
using namespace std;

//LRU: https://www.nowcoder.com/practice/5dfded165916435d9defb053c63f1e84?tpId=295&tqId=2427094&sourceUrl=%2Fexam%2Foj
/*
    用双链表实现O(1)的插入和查询
    利用哈希表实现结点的快速映射
    使用循环链表，用一个哨兵结点即可。dummy—>prev始终指向链表末尾的结点
*/
#include <unordered_map>
class Solution {
    struct Node {
        int k, v;
        Node* prev;
        Node* next;
        Node() = default;
        Node(int k, int v): k(k), v(v), prev(nullptr), next(nullptr) {}
    };
    unordered_map<int, Node*> mp;
    int capacity;
    Node* dummy;

    //从链表中移除一个结点
    void remove(Node* node) {
        node -> next -> prev = node -> prev;
        node -> prev -> next = node -> next;
        node -> prev = node -> next = nullptr;
    }
    //头插
    void insertHead(Node* node) {
        node -> prev = dummy;
        node -> next = dummy -> next;
        node -> prev -> next = node;
        node -> next -> prev = node;
    }

  public:
    Solution(int capacity) {
        this -> capacity = capacity;
        dummy = new Node(0, -1);
        dummy -> next = dummy;
        dummy -> prev = dummy;
    }

    int get(int key) {
        int res = -1;
        if(mp.count(key)) {
            res = mp[key] -> v;
            update(mp[key]);
        }
        return res;
    }

    void set(int key, int value) {
        if(mp.count(key)) {
            mp[key] -> v = value;
            update(mp[key]);
        } else {
            Node* newNode = new Node(key, value);
            insertHead(newNode);
            mp[key] = newNode;
            if(mp.size() > capacity) { //超出容量，取出最近最久未被使用的结点，也就是链表尾部的结点
                auto back = dummy -> prev;
                mp.erase(back -> k);
                remove(back);
                delete back;
            }
        }
    }
    //更新结点，将结点从链表中取出插入链表头部表示刚刚被使用
    void update(Node* node) {
        remove(node);
        insertHead(node);
    }
};