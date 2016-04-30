#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <unordered_map>
#include <utility>  
using namespace std;

const int knight_steps = 8;
const int knight_step_row[] = {-1, -2, -2, -1, 1, 2, 2, 1};
const int knight_step_col[] = {-2, -1, 1, 2, 2, 1, -1, -2};

const int bishop_steps = 4;
const int bishop_step_row[] = {-1, -1, +1, +1};
const int bishop_step_col[] = {-1, +1, +1, -1};

int bishop_dp(vector<vector<char> > &boards, int i, int j, int rows, int cols, int len, unordered_map<char, vector<int> > &dp)
{
    int res = 0;
    // check 4 directions of bishop
    for(int s = 0; s < bishop_steps; ++ s)
    {
        int i_next = i;
        int j_next = j;
        while(true) {
            i_next += bishop_step_row[s];
            j_next += bishop_step_col[s];
            // skip all invalide move of knight
            if(i_next < 0 || i_next >= rows) break;
            if(j_next < 0 || j_next >= cols) break;
            char next = boards[i_next][j_next];
            if(!isdigit(next)) continue;
            res += dp[next][len-1];
        }
    }

    return res;
}

int knight_dp(vector<vector<char> > &boards, int i, int j, int rows, int cols, int len, unordered_map<char, vector<int> > &dp)
{
    int res = 0;
    // check 8 possible steps of knight
    for(int s = 0; s < knight_steps; ++s) {
        
        int i_next = i + knight_step_row[s];
        int j_next = j + knight_step_col[s];
        // skip all invalide move of knight
        if(i_next < 0 || i_next >= rows) continue;
        if(j_next < 0 || j_next >= cols) continue;
        char next = boards[i_next][j_next];
        if(!isdigit(next)) continue;
        res += dp[next][len-1];
    }

    return res;
}

int count(string piece, set<char> &startings, vector<vector<char> > &boards, int len)
{
    int res = 0;
    if(boards.empty()) return res;
    const int rows = boards.size();
    const int cols = boards[0].size();

    int (*count_dp)(vector<vector<char> > &, int, int, int, int, int, unordered_map<char, vector<int> > &);
    if(piece == "knight")
        count_dp = knight_dp;
    else
        count_dp = bishop_dp;
    
    unordered_map<char, vector<int> > dp;

    for(char c = '0'; c <= '9'; ++c)
    {
        dp.insert(make_pair(c, vector<int>(len, 1)));
    }

    for(int l = 1; l < len; ++l)
    {
        for(int i = 0; i < rows; ++i) 
        {
            for(int j = 0; j < cols; ++j) 
            {
                char cur = boards[i][j];
                if(isdigit(cur)) {
                    
                    dp[cur][l] = count_dp(boards, i, j, rows, cols, l, dp);
                    cout << "searching start with " << cur << ", get dp=" << dp[cur][l] << " l=" << l <<endl;
                }
            }
        }
    }

    set<char>:: iterator it;
    for(it = startings.begin(); it != startings.end(); ++it)
    {
        res += dp[*it][len-1];
    }
    
    return res;
}

int main() {

    // read 1 line
    string piece;
    cin >> piece;
    //cout << piece << endl;
    
    // read 2 line
    int len;
    cin >> len;
    //cout << len << endl;
    
    // read 3 line
    string line;
    getline(cin, line);
    getline(cin, line);
    //cout << line << endl;
    stringstream ss(line);
 
    set<char> startings;
    char tmp;
    while(ss >> tmp) {
        if(isdigit(tmp))
            startings.insert(tmp);
    }

    // read 4, 5 line
    int rows, cols;
    cin >> rows;
    cin >> cols;
    //cout << rows << " " << cols << endl;
    
    // read board
    vector<vector<char> > boards(rows, vector<char>(cols, 0));     
    for(int i = 0; i < rows; ++i) 
    {
        for(int j = 0; j < cols; ++j) 
        {
            cin >> tmp;
            boards[i][j] = tmp;
            //cout << tmp << " ";
        }
        //cout << endl;
    }

    cout << count(piece, startings, boards, 3) << endl;

    return 0;
}
