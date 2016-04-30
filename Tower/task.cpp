#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include "SmartPoint.h"

using namespace std;

class Solution {
public:
    vector<int> taskOrder(int N, vector<pair<int, int> >& requests) {
        vector<vector<int>> graph = make_graph(N, requests);
        vector<int> res;
        vector<bool> visited(N, false);

        for(int i = 0; i < N; ++i)
        {
            if(visited[i]) continue;
            dfs(i, visited, graph, res);
        }

        return res;
    }
private:
    vector<vector<int> > make_graph(int N, vector<pair<int, int> >& requests) {
        vector<vector<int> > graph(N);

        for(auto pre : requests)
            graph[pre.second].push_back(pre.first);

        for(auto &g: graph)
            sort(g.begin(), g.end());
        
        return graph;
    }
    
    bool dfs(int node, vector<bool> &visited, vector<vector<int> >& graph,  vector<int> &res)
    {


        if (visited[node]) return false;
        if(graph[node].size() == 0) res.push_back[node]
    
        visited[node] = true; 
        for (int neigh : graph[node])
            if ( dfs(i, visited, graph, res));


        return false;
    }
};
 

int main() {

    Solution sol;
    int T;
    cin >> T;

    for(int i = 0; i < T; ++i)
    {
        int N, M, ti, tj;
        cin >> N >> M;
        vector<pair<int, int> > prerequests;
        for(int j = 0; j < M; ++j) {
            cin >> ti >> tj;
            prerequests.push_back(make_pair(ti, tj));
        }
        vector<int> res = sol.taskOrder(N, prerequests);
        for(int i = 0; i < res.size(); ++i)
            cout << res[i] << " ";
        cout << endl;
    }
    
    return 0;
}
