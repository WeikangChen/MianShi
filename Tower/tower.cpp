#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
typedef std::vector< std::vector<unsigned int> > TestEntries;

using namespace std;


/*
 * Complete the function below.
 */
vector < unsigned int > stockMaximize(TestEntries testEntries)
{
    vector<unsigned int> result;
    int testNumber=1;
    for (TestEntries::const_iterator iterTest = testEntries.begin(); iterTest != testEntries.end(); ++iterTest)
    {
        //cout << "Test#[" << testNumber << "]";
        const vector<unsigned int>& testEntry = *iterTest;
        std::size_t priceIndex = 1;
        for (vector<unsigned int>::const_iterator iterPrice = testEntry.begin(); iterPrice != testEntry.end(); ++iterPrice)
        {
            //cout << " Price" << priceIndex++ << " [" << *iterPrice << "]";
        }
        //cout << endl;
        ++testNumber;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    vector < unsigned int > res;
    unsigned int _tests;
    cin >> _tests;
    //cout << "Will have #[" << _tests << "] Tests" << endl;
    TestEntries testEntries;

    for ( unsigned int _testNum=1; _testNum<=_tests; ++_testNum )
    {
        testEntries.push_back(vector<unsigned int>());
        int _prices_size = 0;
        cin >> _prices_size;
        //cout << "Test #[" << _testNum << "] Test will have [" << _prices_size << "] prices" << endl;
        int _prices_item;
        for(int _prices_i=0; _prices_i<_prices_size; _prices_i++)
        {
            cin >> _prices_item;
            testEntries.back().push_back(_prices_item);
            //cout << "Test #[" << _testNum << "] Pushed back [" << _prices_item << "]" << endl;
        }
    }
    res = stockMaximize(testEntries);
    for(unsigned int res_i=0; res_i < res.size(); res_i++)
    {
        fout << res[res_i] << endl;;
    }

    fout.close();
    return 0;
}

long stringSimilarity(string value) {
    long res = 0;
    const int n = value.size();
    vector<int> olap(n, -1);

    int j = -1;
    for(int i = 1; i < n; ++i) {
        while(j > -1 && value[i] != value[j+1]) j = value[j];
        if(value[i] == value[j+1]) j++;
        olap[i] = j;
        res +=  (j != -1 ? (j+1) : 0);
    }
    
    return res;
}
