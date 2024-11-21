#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<ctime>
#include<iomanip>
using namespace std;

/*
    1. PRIORITY Next improve memory consumption in the store file part
    by popping list items whenever processed instead of at the end
    2. Also figure out how to use malloc (not important)
*/ 

void newfile(string filename, string data){
    ofstream input(filename);
    input << data;
    input.close();
}
int main(int argc, char *argv[]){
    time_t start = time(NULL);
    cout << "start init" << endl;
    int num;
    if(argc == 1){
        num = 100;
    }else{
        num = stoi(argv[1]);
    }
    vector<bool> primes(num + 1, true);
    primes[0] = false; primes[1] = false;
    cout << "end init" << endl;
    for (int i = 2; i <= sqrt(num); i++) {
        if (primes[i]) {
            for (int j = i * i; j <= num; j += i) {
                primes[j] = false;
            }
        }
    }
    cout << endl << "storing files" << endl;
    string final("");
    for(int i = 0; i<=primes.size(); i++){
        if(primes[i]){
            final += to_string(i) + string(",");
        }
    }
    newfile(string("primes.txt"), final);
    time_t finish = time(NULL);
    double time = double(finish) - double(start);
    cout << "it took " << setprecision(15) << time << " seconds." << endl;
    return 0;
}