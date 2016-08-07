#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<string, string> hsNext;
string longest_head;

int longestUtil(vector<unordered_map<string, int>> &words_chain, int from, string word) {

    int cur_size = word.size();
    if (cur_size == 1) return 1;
    int longest_chain = words_chain[cur_size][word];
    if (longest_chain) return longest_chain;
        
    for (int i = 0; i < cur_size; ++i) {
        string new_word = word.substr(0, i) + word.substr(i+1);
        if (words_chain[cur_size-1].find(new_word) != words_chain[cur_size-1].end()) {
            int new_chain = longestUtil(words_chain, from, new_word) + 1;
            if (new_chain > longest_chain) {
                hsNext[word] = new_word;
                longest_chain = new_chain;
            }
        }
    }
    if (!longest_chain) longest_chain = 1;
    words_chain[cur_size][word] = longest_chain;
    return longest_chain;
}


int longest(vector<string> &dict) {
    vector<unordered_map<string, int >> words_chain;
    int max_len = 0;
    
    for (auto &d: dict) {
        int l = d.size();
        max_len = max(max_len, l);
        if (l >= words_chain.size()) words_chain.resize(l+1);
        words_chain[l][d] = 0;
    }

    int res = 0;
    for (int i = max_len; i > 0; --i) 
    {
        //if (i <= res) break;
        cout << " Lenght of " << i << " words are:" << endl;
        for (auto it = words_chain[i].begin(); it != words_chain[i].end(); ++it)
        {
            int tmp = longestUtil(words_chain, i, it->first);
            if (tmp > res) {res = tmp; longest_head = it->first;}
            cout << "\t" << it->first << ", length = " << it->second << endl;
        }
        cout << endl;
    }

    
    return res;
}

int helper(string w, vector<unordered_map<string, int>> &dict)
{
    int cur_len = w.size();
    if (cur_len == 1) return dict[cur_len][w] = 1;
    int cur_max_res = dict[cur_len][w];
    if (cur_max_res) return cur_max_res;
    int next_len = cur_len - 1;
    int res = 0;
    for (int i = 0; i < cur_len; ++i){
        string new_word = w.substr(0, i)+ w.substr(i+1);
        if (dict[next_len].find(new_word) != dict[next_len].end()) {
            res = max(res, helper(new_word, dict)+1);
        }
    }
    
    return dict[cur_len][w] = res;
}

int longestChain(vector < string > words) {
    vector<unordered_map<string, int>> dict(51);
    int max_len = 0;
    for (auto &w: words) {
        int cur_len = w.size();
        max_len = max(max_len, cur_len);
        dict[cur_len][w] = 0;
    }
    
    int res = 0;
    for (int i = max_len; i > 0; --i) {
        if (res >= i) break;
        for (auto &w: dict[i]) {
            res = max(res, helper(w.first, dict));
        }
    }
    return res;
}

int main(int argc, char *argv[])
{
    vector<string> dict =  {"asdf", "a", "1235", "b", "ab", "12345", "bc", "ac", "135", "xyz", "abc", "1X2345", "abcd", "axbcd", "axybcd", "1X234X5", "dfasdqw", "asdf", "eqweqa", "asdqw", "fasdqw", "xy", "yz", "z", "axyzbcd"};
    cout << "longest chain's length is " << longest(dict) << ": ";
    string cur = longest_head;
    cout << cur;
    while (hsNext.find(cur) != hsNext.end()) {
        cur = hsNext[cur];
        cout << "-> "<< cur;
    }
    cout << endl;
	return 0;
}


/*
int main() {
    ofstream fout(getenv("OUTPUT_PATH"));
    int res;
    
    int _words_size = 0;
    cin >> _words_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<string> _words;
    string _words_item;
    for(int _words_i=0; _words_i<_words_size; _words_i++) {
        getline(cin, _words_item);
        _words.push_back(_words_item);
    }
    
    res = longestChain(_words);
    fout << res << endl;
    
    fout.close();
    return 0;
}
*/

/*
int longestChain(vector < string > words) {
    vector<unordered_map<string, int>> dict(51);
    int max_len = 0;
    for (auto &w: words) {
        int cur_len = w.size();
        max_len = max(max_len, cur_len);
        dict[cur_len][w] = 0;
        if (cur_len == 1) dict[cur_len][w] = 1;
    }
    
    int res = 0;
    for (int i = 2; i <= max_len; ++i) {
        for (auto &p: dict[i]) {
            int cur_res = 1;
            int pre_len = i - 1;
            string w = p.first;
            for (int j = 0; j < i; ++j){
                string new_word = w.substr(0, j)+ w.substr(j+1);
                if (dict[pre_len].find(new_word) != dict[pre_len].end()) {
                    cur_res = max(cur_res, dict[pre_len][new_word] + 1);
                }
            }
            dict[i][w] = cur_res;
            res = max(res, cur_res);
        }
    }
    return res;
}
*/
