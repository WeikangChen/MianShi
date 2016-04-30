#include <iostream>
#include <vector>

using namespace std;

string segment_sort(string &s) //assuming the string is alphanumeric
{
    const int n = s.size();
    if(n == 0) return s;

    bool isdigit_pre = isdigit(s[0]); // if not digit then alpha, n > 0, s[0] is safe
    size_t start_pre = 0;
    string::iterator it0 = s.begin();
    for(int i = 1; i < s.size(); ++i)
    {
        char c = s[i];
        bool isdigit_cur = isdigit(c);
        if(isdigit_pre != isdigit_cur)
        {
            sort(it0+start_pre, it0+i);
            start_pre = i;
            isdigit_pre = isdigit_cur;
        }
    }
    sort(it0+start_pre, s.end());
    return s;
}

int main(int argc, char ** argv)
{
    string s1("");
    segment_sort(s1);
    cout << s1 << endl;

    string s2("AZQF013452BAB");
    segment_sort(s2);
    cout << s2 << endl;

    string s3("asdfasd2123123fdfAZQF013452ASDAS123123");
    segment_sort(s3);
    cout << s3 << endl;

    return 0;
}
