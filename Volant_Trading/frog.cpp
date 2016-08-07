#include <queue> 
#include <iostream>
#include <vector>


using namespace std;

int solution(int X, vector<int> &A) {
    priority_queue<int, vector<int>, greater<int>> pq;
    const int D = 1;
    const int N = A.size();
    int cur = 0;
    if (cur + D > X) return 0;
    
    for (int i = 0; i < N; ++i) {
        if (A[i] <= cur) continue;

        pq.push(A[i]);
        while (!pq.empty() && pq.top() <= cur + D) {
            cur = pq.top(); pq.pop();
        }
        
        if (cur + D > X) return i;
    }
    return -1;
}



int main(int argc, char *argv[])
{
    vector<int> A = {6, 5, 4, 3, 2, 1};
    cout << solution(6, A) << endl;

    vector<vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9,10, 11, 12}};

    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        for (auto is = it->begin(); is != it->end(); ++is) {
            cout << *is << " ";
        }
        cout << endl;
    }
    return 0;
}

