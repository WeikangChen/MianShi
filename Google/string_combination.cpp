#include <iostream>
#include <vector>

using namespace std;

void helper(string str, int p , vector<string> &res)
{
    if(p == str.size())
        res.push_back(str);
    else if(str[p] == '?') {
        str[p] = '0';
        helper(str, p+1, res);
        str[p] = '1';
        helper(str, p+1, res);
    }
    else {
        helper(str, p+1, res);
    }

}

vector<string> str_combination(string str)
{
    vector<string> res;
    helper(str, 0, res);
    return res;
}


int main(int argc, char ** argv)
{
    vector<string> res = str_combination("101?100??1");
    for(int i = 0; i < res.size(); ++i)
        cout << res[i] << endl;

    return 0;
}
