#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

string longest_palindrome(string s)
{
    const int n = s.size();
    if(n == 0) return s;
    bool hs[n][n];     // DP idea: hs[j][i] == true means s.substr(j, i-j+1) is palindrome
    memset(hs, false, n*n);

    int pos = 0;
    int len = 1;
    for(int i = 0; i < n; ++i)
    {
        hs[i][i] = true;
        for(int j = i-1; j > -1; --j)
        {
            if(s[j] == s[i] && (j+2>=i || hs[j+1][i-1]))
            {
                hs[j][i] = true;
                int cur_len = i - j + 1;
                if(cur_len > len){
                    len = cur_len;
                    pos = j;
                }
            }
        }
    }

    return s.substr(pos, len);
}

int main(int argc, char ** argv)
{
    cout << longest_palindrome("") << endl;
    cout << longest_palindrome("T") << endl;
    cout << longest_palindrome("TABBA") << endl;
    cout << longest_palindrome("TSASADADASASDASDABBA") << endl;
    return 0;
}
