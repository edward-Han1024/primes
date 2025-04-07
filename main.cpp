#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<ctime>
#include<iomanip>
#include<math.h>
#include<cstdint>
using namespace std;

/*
    1. check only odd #s and push 2
    2. Figure out how to use malloc (not important)
*/

int main(int argc, char *argv[]){
    time_t start = time(NULL);
    cout << "start init" << endl;
    unsigned long num;
    if(argc == 1){
        num = 100;
    }else{
        num = stoul(argv[1]);
    }
    vector<bool> primes(num + 1, true);
    primes[0] = false; primes[1] = false;
    cout << "end init" << endl;
    unsigned long limit = sqrt(num);
    for (unsigned long i = 2; i <= limit; i++) {
        if (primes[i]) {
            for (unsigned long j = i * i; j <= num; j += i) {
                primes[j] = false;
            }
        }
    }
    cout << endl << "storing files" << endl;
    ofstream file("primes.txt");
    unsigned long size = primes.size();
    for(unsigned long i = 0; i<=size; i++){
        if(primes[i]){
            file << to_string(i) << " ";
        }
    }
    time_t finish = time(NULL);
    double time = double(finish) - double(start);
    cout << "it took " << setprecision(15) << time << " seconds." << endl;
    return 0;
}