#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#define RANGE 10

void count_sort(int *p, int N)  // count how occurance of number between [1, RANGE], similar to count sort, time complex ~O(n)
{
    int count[RANGE + 1];
    memset(count, 0, sizeof(count));
    
    for(int i = 0; i < N; ++i)
        ++count[p[i]];

    
    for(int i = 1; i <= RANGE; ++i)
    {
        count[i] += count[i-1];
        for(int j = count[i-1]; j < count[i]; ++j)
        {
            p[j] = i;
        }
    }
}

int main(int argc, char ** argv)
{
    const int N = 100;// N could be one million
    int array[N];
    
    srand(time(NULL));
    for(int i = 0; i < N; ++i)  // generate random test case
        array[i] = 1 + 1.0 * RANGE * rand() / RAND_MAX;

    cout << "Before sort:" << endl;
        for(int i = 0; i < N; ++i)
        cout << array[i] << " ";
        cout << endl << endl;
    
    count_sort(array, N);

    cout << "After sort:" << endl;
    for(int i = 0; i < N; ++i)
        cout << array[i] << " ";
    cout << endl << endl;
    
    return 0;
}
