#include<bits/stdc++.h>
//#define TIME
using namespace std;
//Please replace 51nod1577 with your problem name.

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
        system("51nod1577mker > dat.txt");
        #else
        system("./51nod1577mker > dat.txt");
        #endif
        #ifdef TIME
        cout<<"Data Made"<<endl;
        cout<<"Running Mine"<<endl;
        t1 = GetCycleCount();
        #endif
        #ifdef WIN32
        system("51nod1577_rb < dat.txt > my.txt");
        #else
        system("./51nod1577_rb < dat.txt > my.txt");
        #endif
        #ifdef TIME
        t2 = GetCycleCount();
        cout<<"time used :: "<<(t2-t1)*1000/FREQUENCY<<"ms"<<endl;
        cout<<"Running std"<<endl;
        t1 = GetCycleCount();
        #endif
        #ifdef WIN32
        system("51nod1577 < dat.txt > std.txt");
        #else
        system("./51nod1577 < dat.txt > std.txt");
        #endif
        #ifdef TIME
        t2 = GetCycleCount();
        cout<<"time used :: "<<(t2-t1)*1000/FREQUENCY<<"ms"<<endl;
        cout<<"diffing answer"<<endl;
        #endif
        #ifdef WIN32
        if( system("fc my.txt std.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
        #else
        if( system("diff my.txt std.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
        #endif
    }
}
