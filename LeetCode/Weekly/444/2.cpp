#include<bits/stdc++.h>
using namespace std;


//https://leetcode.cn/problems/implement-router/
/*
    由于时间是递增的，因此直接使用队列模拟，为了防止删除操作占用时间，使用pair<vector<int>, int>
    来模拟队列，其中 vector 是队列本身，第二个 int 为队首指针，模拟出队。
*/
class Router {
    int capacity;
    queue<tuple<int, int, int>> packq;
    set<tuple<int, int, int>> st;
    unordered_map<int, pair<vector<int>, int>> dtmap;  //第一个为队列，第二个为队首指针
public:
    Router(int memoryLimit) { capacity = memoryLimit; }

    bool addPacket(int source, int destination, int timestamp) {
        auto newPackect = tie(source, destination, timestamp);
        if (st.contains(newPackect)) {
            return false;
        }
        if(packq.size() == capacity) {
            forwardPacket();
        }
        packq.push(newPackect);
        st.insert(newPackect);
        dtmap[destination].first.push_back(timestamp);
        return true;
    }

    vector<int> forwardPacket() {
        if (packq.empty())
            return {};
        auto [s, d, t] = packq.front();
        vector<int> ret = {s, d, t};
        packq.pop();
        st.erase(tie(s, d, t));
        dtmap[d].second ++ ;
        return ret;
    }

    int getCount(int destination, int startTime, int endTime) {
        auto& [times, head] = dtmap[destination];
        auto p0 = lower_bound(times.begin() + head, times.end(), startTime);
        auto p1 = upper_bound(times.begin() + head, times.end(), endTime);

        return p1 - p0;
    }
};
    
    /**
     * Your Router object will be instantiated and called as such:
     * Router* obj = new Router(memoryLimit);
     * bool param_1 = obj->addPacket(source,destination,timestamp);
     * vector<int> param_2 = obj->forwardPacket();
     * int param_3 = obj->getCount(destination,startTime,endTime);
     */