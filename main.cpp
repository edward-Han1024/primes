#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdint>
#include <chrono>
#include "miller-rabin.hpp"
using namespace std;

/*
    TODO improve algorithm further
        DONE find out how to improve algorithm
        TODO implement it
        TODO make sure it works!
    TODO implement spot checks
        DONE implement miller rabin test
        TODO test the miller rabin test
        TODO do miller rabin tests on a different thread
    TODO Figure out how to use malloc (not important)
*/


// Defs
void basic_sieve(unsigned long &num, unsigned long &limit, vector<bool> &primes);
vector<bool> basic_wrapper(unsigned long lnum);
long long difference(chrono::system_clock::time_point start);

// Main code
int main(int argc, char *argv[])
{
    unsigned long num;
    if (argc == 1)
    {
        num = 100;
    }
    else
    {
        num = stoul(argv[1]);
    }
    cout << "start sieve" << endl;
    vector<bool> primes = basic_wrapper(num);
    chrono::system_clock::time_point start = chrono::system_clock::now();
    cout << endl << "storing files" << endl;
    ofstream file("primes.txt");
    file << "2 ";
    num = primes.size();
    for (unsigned long i = 0; i < num; i++)
    {
        if (primes[i])
        {
            file << to_string(2 * i + 3) << " ";
        }
    }
    cout << "file storage took " << difference(start) << "ms" << endl;
    return 0;
}

long long difference(chrono::system_clock::time_point start){
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() -\
    chrono::duration_cast<chrono::milliseconds>(start.time_since_epoch()).count();
}

vector<bool> basic_wrapper(unsigned long lnum){
    chrono::system_clock::time_point start = chrono::system_clock::now();
    cout << "start init" << endl;
    unsigned long num = (lnum - 1) / 2;
    vector<bool> primes(num, true);
    unsigned long limit = (sqrt(2 * num + 3) - 1)/ 2;
    cout << "init took " << difference(start) << "ms, start main" << endl;
    start = chrono::system_clock::now();
    basic_sieve(num, limit, primes);
    cout << "main loop took " << difference(start) << "ms" << endl;
    cout << "finished sieve" << endl;
    return primes;
}

void basic_sieve(unsigned long &num, unsigned long &limit, vector<bool> &primes){
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
}