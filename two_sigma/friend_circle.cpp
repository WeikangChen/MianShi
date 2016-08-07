#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;


int find(vector<int> &parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

int friendCircles(vector < string > friends) {
    const int N = friends.size();
    vector<int> parent(N, -1);
    vector<int> rank(N, 1);
    int cnt = N;
    for (int i = 0; i < N; ++i) 
        parent[i] = i;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (friends[i][j] == 'N') continue;
            int pi = find(parent, i);
            int pj = find(parent, j);
            if (pi != pj) {
                if (rank[pi] < rank[pj])
                    parent[pi] = pj;
                else if (rank[pi] > rank[pj])
                    parent[pj] = pi;
                else {
                    parent[pj] = pi;
                    rank[pi] ++; 
                }
                cnt --;
            }
        }
    }
    return cnt;
}

int main(int argc, char *argv[])
{
}
