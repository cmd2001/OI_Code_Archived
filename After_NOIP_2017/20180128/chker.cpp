#include<bits/stdc++.h>
using namespace std;

int main() {
    static int cse = 0;
    while( 1 ) {
        printf("Case :: %d\n",++cse);
        system("bzoj2555mker.exe > dat.txt");
        system("bzoj2555.exe < dat.txt > my.txt");
        system("bzoj2555std.exe < dat.txt > std.txt");
        if( system("fc my.txt std.txt") ) {
            puts("===============!!!WA!!!===============");
            getchar() , getchar();
        }
    }
}
