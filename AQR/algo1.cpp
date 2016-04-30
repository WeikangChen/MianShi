#include <iostream>
#include <vector>

using namespace std;

double power(int P, int Q) // recursive method, time comple O(lg(Q)) 
{
    // Q could only be <, = , > with 0
    if(Q == 0)
    {
        return 1;
    }
    else if(Q < 0)
    {
        return 1.0 / power(P, -Q);
    }
    else { // Q > 0 
	double tmp = power(P, Q/2);
        if(Q & 1) // Q is odd
            return tmp * tmp * P;
        else   // Q is even
            return tmp * tmp;
    }
    
}

int main(int argc, char ** argv)
{
    cout << power ( 5, 0) << endl;
    cout << power ( 2, 10) << endl;
    cout << power ( 3, -2) << endl;
    return 0;
}
