#include<bits/stdc++.h>
using namespace std;

/*
    字典树： 
    https://oi-wiki.org/string/trie/
    https://leetcode.cn/problems/implement-trie-prefix-tree/solutions/2993894/cong-er-cha-shu-dao-er-shi-liu-cha-shu-p-xsj4/

    例题：
    [Leetcode]208. 实现Trie https://leetcode.cn/problems/implement-trie-prefix-tree/description/
*/

class Trie {
    struct Node {
        Node* son[26] {};
        bool end = false;            //表示当前节点是否为一个字符串的结尾
    };
    Node* root;

    /*
        查找 word 是否在 Trie 中
    */
    int find(string word) {
        Node* cur = root;

        for(char c: word) {
            int id = c - 'a';
            if(cur -> son[id] == nullptr) {
                return 0;   //字典树中没有字符串
            }
            cur = cur -> son[id];
        }

        return cur -> end ? 2 : 1; 
    }

public:
    Trie() { 
        root = new Node(); 
    }
    
    void insert(string word) {
        Node* cur = root;
        for(auto c: word) {
            c -= 'a';
            if(cur -> son[c] == nullptr) {
                cur -> son[c] = new Node();
            }
            cur = cur -> son[c];
        }
        cur -> end = true;
    }
    
    bool search(string word) {
        return find(word) == 2;
    }
    
    bool startsWith(string prefix) {
        return find(prefix) != 0;
    }
};
