#include <iostream>
#include <vector>

using namespace std;

class base
{
public:
    virtual int fun() = 0;
};

int base:: fun()
{
    cout <<  "hello world " << endl;
    return 0;
}

class derive: public base
{
public:
    int fun() {
        base::fun();
        return 0;
    }
};

int main(int argc, char ** argv)
{
    derive d;
    d.fun();
    return 0;
}
