#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;

// obj.set("A", 0.4);
// obj.set("B", 0.6);
// obj.next(); "A" 40% and "B" 60%
// obj.set("A", 0.6);
// obj.next(); "A" 50% and "B" 50%
// obj.set("A", 0.)
// obj.next(); "B" 100%

/*
class Obj {
    unordered_map<string, double> dict;
    vector<double> acc_vec;
    vector<string> str_vec;
public:
    void set(const string& str, double val) {
        dict[str] = val;
        double sum = 0.0;
        for (auto& p: dict) {
            sum += p.second;
        }
        acc_vec.clear();
        str_vec.clear();
        double acc = 0.0;
        for (auto& p: dict) {
            acc += p.second / sum;
            cout << p.first << " acc= " << acc << endl;
            acc_vec.emplace_back(acc); // {{0.4, "A"}, {1.0, "B"}}
            str_vec.emplace_back(p.first);
        }
        
    }
    string next() {
        if (acc_vec.empty())
            return "";
        double r = double(std::rand()) / (RAND_MAX + 1u);
        auto it = lower_bound(acc_vec.begin(), acc_vec.end(), r);
        auto idx = distance(acc_vec.begin(), it);
        // cout << "rand=" << r << " idx=" << idx << "\t"; 
        return str_vec[idx];
    }
    
};
*/

class Random {
    unordered_map<string, size_t> dict;
    vector<string> strs;
    vector<double> probs;
public:
    Random() {
        strs.push_back("");
        probs.push_back(0.0);
    }
    void set(const string& str, double p) {
        const auto N = strs.size();
        auto it = dict.find(str);
        if (it == dict.end()) {
            dict.insert(make_pair(str, N));
            strs.push_back(str);
            probs.push_back(probs[N-1] + p);
        } else {
            auto idx = it->second;
            const auto diff = p + probs[idx-1] - probs[idx];
            while (idx < N) {
                probs[idx] += diff;
                idx += idx & (-idx);
            }
        }
    }
    string next() {
        if (probs.size() == 1)
            return "";
        const auto r = double(rand()) / (RAND_MAX) * probs.back();
        auto it = lower_bound(probs.begin(), probs.end(), r);
        auto idx = distance(probs.begin(), it);
        return strs[idx];
    }
};

int main() {
    Random obj;
    obj.set("A", 0.4);
    obj.set("B", 0.6);
    obj.set("C", 1.2);
    unordered_map<string, int> stat;
    const int tot = 1000000;
    for (int i = 0; i < tot; ++i) {
        const auto str = obj.next();
        stat[str]++;
    }
    cout << "tot=" << tot << endl;
    for (auto& p: stat) {
        cout << "str=" << p.first << " occ_prob=" << 100 * p.second / double(tot) << "% \n";
    }
// obj.set("A", 0.6);
// obj.next(); "A" 50% and "B" 50%
// obj.set("A", 0.)
// obj.next(); "B" 100%
    return 0;
}
