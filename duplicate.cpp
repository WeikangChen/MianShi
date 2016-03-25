#include <iostream>
#include <vector>

using namespace std;

vector<int> find_overlap(vector<int> va, vector<int> vb)
{
    
    vector<int> res;
    const int m = va.size();
    const int n = vb.size();
    if(m == 0 || n == 0) return res;
    
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());

    int i = 0, j = 0;
    while(i < m && j < n)
    {
        if(va[i] < vb[j])
            i++;
        else if(va[i] > vb[j])
            j++;
        else {
            res.push_back(va[i]);
            i++;
            j++;
        }
    }

    return res;
}

int fun(int *a)
{
    cout << "size of para = "<< sizeof(a)/sizeof(int) << endl;
    return sizeof(a)/sizeof(int);
}

int main(int argc, char ** argv)
{
    int a[] = {1,2,3,4,5,6,7,8,9};
    int b[] = {2,4,6,8,10};

    cout << "size of a = "<< sizeof(a)/sizeof(int) << endl;
    cout << "size of b = "<< sizeof(b)/sizeof(int) << endl;
    
    fun(a);
    fun(b);
    vector<int> va(a, a+sizeof(a)/sizeof(int));
    vector<int> vb(b, b+sizeof(b)/sizeof(int));
    
    vector<int> overlap = find_overlap(va, vb);

    
    for(int i = 0; i < overlap.size(); ++i)
    {
        cout << overlap[i] <<  ", ";
    }
    cout << endl;
    return 0;
}
