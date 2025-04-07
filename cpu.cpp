#include<cstdlib>
#include<unistd.h>
#include<iostream>
#include<string>
#include<ncurses.h>
#include<fstream>
#include<sstream>
using namespace std;

int main(){
    initscr();
    while(true){
        clear();
        move(1,1);
        system("ps -Opmem=PMEM,pcpu=PCPU,nice > temp.txt");
        ifstream file("temp.txt");
        ostringstream stream;
        stream << file.rdbuf();
        printw(stream.str().c_str());
        refresh();
        getch();
    }
}