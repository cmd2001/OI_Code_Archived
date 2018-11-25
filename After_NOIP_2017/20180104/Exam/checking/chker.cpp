#include<bits/stdc++.h>
using namespace std;

int main() {
    static int cse = 0;
    while( 1 ) {
        cout<<"Case :: "<<++cse<<endl;
        system("./t3mker > dat.txt");
        system("./t3test < dat.txt > vio.txt");
        system("./t3test2 < dat.txt > ans.txt");
        if( system("diff ans.txt vio.txt") ) {
            puts("-----------------WA------------------");
            system("pause");
        }
    }
    return 0;
}