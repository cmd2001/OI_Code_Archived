#include<bits/stdc++.h>
using namespace std;

int main() {
    int cst = 0;
    while( 1 ) {
        cout<<"Case :: "<<++cst<<endl;
        system("./bzoj2821mker");
        system("./bzoj2821");
        system("./bzoj2821std");
        if( system("diff my.txt std.txt") )
            return 0;
    }
}