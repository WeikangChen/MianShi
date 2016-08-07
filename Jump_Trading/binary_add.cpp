// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
#include <map>
#include <vector>

#include <iostream>
#include <vector>

using namespace std;


int solution(vector<int> &A) {
    map<int, int> mp;
    const int N = A.size();
    
    for (int i = 0; i < N; ++i) {
        if (A[i] & 1)
            mp[A[i]]--;
        else
            mp[A[i]]++;
    }
    mp[24]++;
    int car = 0;
    for (int i = 0; i < 25; ++i) {
        int tmp = mp[i] + car;
        mp[i] = tmp % 2 ? 1 : 0;
        car = (tmp - mp[i]) / 2;
        if(mp[i] != 0) cout << i << ":" << mp[i] << endl;
    }

    int pre = 24;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        if (it->first < 25) continue;
        int n = (it->first - pre);
        int M = (1 << (n-1));
        if (car % M != 0) {
            cout << "car =" << car << endl;
            return -1;
        }
        int tmp = (it->second + (car >> (n-1)));
        int rem = (tmp % 2) ? 1 : 0;
        if (rem) {
            cout << "car =" << car << endl;
            cout << "tmp =" << tmp << endl;
            cout << "rem =" << rem << endl;
            return -1;
        }
        car = (tmp - rem) / 2;
        pre = it->first;
    }
    cout << "car =" << car << endl;
    if (car) return -1;
    int res = 0;
    for (int i = 0; i < 25; ++i) {
        if(mp[i]) {
            cout << i << ":" << mp[i]<< endl;
            res |= (1 << i);
        }
    }
    res -= (1 << 24);
    return res;
}
    
int main(int argc, char *argv[])
{
    vector<int> a =  {100,100,101};
    cout << "res=" << solution(a) << endl;

    return 0;
}
