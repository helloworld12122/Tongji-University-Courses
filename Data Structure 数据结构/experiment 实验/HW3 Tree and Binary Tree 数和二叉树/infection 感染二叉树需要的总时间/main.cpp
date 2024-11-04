#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;
 
int timeNeededToInfectAll(int n, int start, vector<pair<int, int>>& edges) {
    if (n == 1) return 0;  // 只有一个节点时直接返回 0 分钟
 
    // 使用邻接表存储树，即图的形式
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        int left = edges[i].first, right = edges[i].second;
        if (left != -1) {
            graph[i].push_back(left);
            graph[left].push_back(i);  // 父节点和左子节点双向连接
        }
        if (right != -1) {
            graph[i].push_back(right);
            graph[right].push_back(i);  // 父节点和右子节点双向连接
        }
    }
 
    // BFS 使用队列
    queue<int> q;
    vector<int> visited(n, -1);  // -1 表示未访问
    q.push(start);
    visited[start] = 0;  // 起始节点从0分钟开始
 
    int max_time = 0;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        int current_time = visited[current];
 
        // 遍历所有邻居
        for (int neighbor : graph[current]) {
            if (visited[neighbor] == -1) {  // 如果未访问
                visited[neighbor] = current_time + 1;
                q.push(neighbor);
                max_time = max(max_time, visited[neighbor]);  // 更新最大感染时间
            }
        }
    }
 
    return max_time;
}
 
int main() {
    int n, start;
    cin >> n >> start;
    vector<pair<int, int>> edges(n);
    
    for (int i = 0; i < n; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    
    cout << timeNeededToInfectAll(n, start, edges) << endl;
 
    return 0;
}
