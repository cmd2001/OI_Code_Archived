#include<bits/stdc++.h>
using namespace std;

int main() {
    int cc = 0;
    while( 1 ) {
        printf("Case :: %d\n",++cc);
        system("./t1mker > dat.txt");
        system("./t1_70pts < dat.txt > ans.txt");
        system("./t1_vio < dat.txt > std.txt");
        if( system("diff ans.txt std.txt") ) {
            puts("--------------WA------------------");
            system("pause");
            getchar();
        }
    }
}