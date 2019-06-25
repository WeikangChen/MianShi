#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
 * Complete the function below.
 */

bool dfs(const string &str, const vector<string> &dict, const size_t N,
         const size_t L, int cur, vector<int> &res, vector<int> &cnt) {
  if (cur == L ) {
    return std::all_of(cnt.begin(), cnt.end(),
                       [](const int x) { return x > 0; });
  }
  for (int i = 0; i < N; ++i) {
    const auto &word = dict[i];
    if (str.substr(cur, word.size()) != word)
      continue;
    res.push_back(i);
    ++cnt[i];
    if (dfs(str, dict, N, L, cur + word.size(), res, cnt))
      return true;
    res.pop_back();
    --cnt[i];
  }
  return false;
}

string restore_spaces(const string &str, const vector<string> &dict) {
  const auto L = str.size();
  const auto N = dict.size();
  vector<int> cnt(N, 0);
  vector<int> res;
  res.reserve(N);
  dfs(str, dict, N, L, 0, res, cnt);
  string rs = dict[res[0]];
  for (int i = 1; i < res.size(); ++i) {
    rs += " ";
    rs += dict[res[i]];
  }
  return rs;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));
    string res;
    string _inputString;
    getline(cin, _inputString);
    
    vector<string> _dictionary;
    string _dictionary_item;
    while (cin.good()) {
        getline(cin, _dictionary_item);
        if (_dictionary_item.empty()) continue;
        _dictionary.emplace_back(std::move(_dictionary_item));
    }
    
    res = restore_spaces(_inputString, _dictionary);
    fout << res << endl;
    
    fout.close();
    return 0;
}

/*
investinthepeanutbutterindustry
butter
industry
invest
in
peanut
the
*/
