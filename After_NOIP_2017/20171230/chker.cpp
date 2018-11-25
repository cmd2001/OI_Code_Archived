#include<bits/stdc++.h>
using namespace std;

int main() {
    int cst = 0;
    while( 1 ) {
        cout<<"Case :: "<<++cst<<endl;
        system("./SPOJLCS2mker");
        system("./SPOJLCS2 > wa.txt");
        system("./SPOJLCS2std > std.txt");
        if( system("diff wa.txt std.txt") )
            return 0;
    }
}