#include<bits/stdc++.h>
using namespace std;

// Please replace __problem__name__ with your own problem name .

int main() {
    static int cse = 0;
    while(1) {
        fprintf(stderr,"Case :: %d\n",++cse);
        #ifdef WIN32
        system("__problem__name__mker.exe > dat.txt");
        system("__problem__name__.exe < dat.txt > my.txt");
        if(system("__problem__name__spj.exe")) getchar() , getchar();
        #else
        system("./__problem__name__mker.exe > dat.txt");
        system("./__problem__name__.exe < dat.txt > my.txt");
        if(system("./__problem__name__spj.exe")) getchar() , getchar();
        #endif
    }
    return 0;
}
