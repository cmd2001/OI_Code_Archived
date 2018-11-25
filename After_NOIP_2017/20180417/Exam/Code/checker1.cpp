#include<bits/stdc++.h>
//#define TIME
using namespace std;
//Please replace t1 with your problem name.

static __inline__ unsigned long long GetCycleCount(void)
{
        unsigned hi,lo;
        __asm__ volatile("rdtsc":"=a"(lo),"=d"(hi));
        return ((unsigned long long)lo)|(((unsigned long long)hi)<<32);
}


int main() {
    int cse = 0;
    #ifdef TIME
    double t1,t2;
    const long long FREQUENCY = 2700000000LL;
    #endif
    while( 1 ) {
        printf("Case :: %d\n",++cse);
        #ifdef WIN32
        system("t1mker > dat.txt");
        #else
        system("./t1mker > dat.txt");
        #endif
        #ifdef TIME
        cout<<"Data Made"<<endl;
        cout<<"Running Mine"<<endl;
        t1 = GetCycleCount();
        #endif
        #ifdef WIN32
        system("t1 < dat.txt > my.txt");
        #else
        system("./t1 < dat.txt > my.txt");
        #endif
        #ifdef TIME
        t2 = GetCycleCount();
        cout<<"time used :: "<<(t2-t1)*1000/FREQUENCY<<"ms"<<endl;
        cout<<"Running force"<<endl;
        t1 = GetCycleCount();
        #endif
        #ifdef WIN32
        system("t1force < dat.txt > force.txt");
        #else
        system("./t1force < dat.txt > force.txt");
        #endif
        #ifdef TIME
        t2 = GetCycleCount();
        cout<<"time used :: "<<(t2-t1)*1000/FREQUENCY<<"ms"<<endl;
        cout<<"diffing answer"<<endl;
        #endif
        #ifdef WIN32
        if( system("fc my.txt force.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
        #else
        if( system("diff my.txt force.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
        #endif
    }
}
