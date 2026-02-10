#include<cstdlib>
#include<unistd.h>
#include<iostream>
#include<string>
#include<ncurses.h>
#include<fstream>
#include<sstream>
#include<csignal>

void signalHandler(int signum) {
    endwin();
    std::cout << "ended on signal SIGINT" << std::endl;
    exit(0);
}

int main(){
    std::signal(SIGINT, signalHandler);
    initscr();
    while(true){
        clear();
        refresh();
        move(1,1);
        system("ps -Opmem=PMEM,pcpu=PCPU,nice > temp.txt");
        std::ifstream file("temp.txt");
        std::ostringstream stream;
        stream << file.rdbuf();
        printw(stream.str().c_str());
        move(LINES - 2, 0);
        refresh();
        getch();
    }
}