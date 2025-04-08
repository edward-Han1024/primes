#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cstdint>
using namespace std;

/*
    TODO improve algorithm further
        TODO find out how to improve algorithm
        TODO implement it
        TODO make sure it works!
    TODO implement spot checks
        TODO implement miller rabin test
        TODO do miller rabin tests on a different thread
    TODO Figure out how to use malloc (not important)
*/

int main(int argc, char *argv[])
{
    time_t start = time(NULL);
    cout << "start init" << endl;
    unsigned long num;
    if (argc == 1)
    {
        num = 100;
    }
    else
    {
        num = stoul(argv[1]);
    }
    num = (num - 1) / 2;
    cout << num << endl;
    vector<bool> primes(num, true);
    unsigned long limit = (sqrt(2 * num + 3) - 1)/ 2;
    for (unsigned long i = 0; i < limit; i++)
    {
        if (primes[i])
        {
            for (unsigned long j = ((2 * i + 3) * (2 * i + 3) - 3)/ 2; j <= num; j += 2 * i + 3)
            {
                primes[j] = false;
            }
        }
    }
    cout << endl << "storing files" << endl;
    ofstream file("primes.txt");
    for (unsigned long i = 0; i < num; i++)
    {
        if (primes[i])
        {
            file << to_string(2 * i + 3) << " ";
        }
    }
    time_t finish = time(NULL);
    double elapsed_time = double(finish) - double(start);
    cout << "it took " << setprecision(15) << elapsed_time << " seconds." << endl;
    return 0;
}