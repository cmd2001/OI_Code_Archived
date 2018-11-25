#include<bits/stdc++.h>
using namespace std;

int main() {
    int cse = 0;
    double t1,t2;
    while( 1 ) {
        printf("Case :: %d\n",++cse);
        system("./bzoj2325mker > dat.txt");
        cout<<"Data Made"<<endl;
        cout<<"Running Mine"<<endl;
        t1 = clock();
        system("./bzoj2325ndb < dat.txt > my.txt");
        t2 = clock();
        cout<<"time used :: "<<(t2-t1)<<"ms"<<endl;
        cout<<"Running std"<<endl;
        t1 = clock();
        system("./bzoj2325std < dat.txt > std.txt");
        t2 = clock();
        cout<<"time used :: "<<(t2-t1)<<"ms"<<endl;
        cout<<"diffing answer"<<endl;
        if( system("diff my.txt std.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
    }
}