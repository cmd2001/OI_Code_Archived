#include<bits/stdc++.h>
using namespace std;

#if defined WIN32
inline unsigned __int64 GetCycleCount()
{
    __asm
    {
        _emit 0x0F;
        _emit 0x31;
    }
}
#else
static __inline__ unsigned long long GetCycleCount(void)
{
        unsigned hi,lo;
        __asm__ volatile("rdtsc":"=a"(lo),"=d"(hi));
        return ((unsigned long long)lo)|(((unsigned long long)hi)<<32);
}
#endif


int main() {
    int cse = 0;
    double t1,t2;
    const long long FREQUENCY = 2700000000LL;
    while( 1 ) {
        printf("Case :: %d\n",++cse);
        system("./bzoj3626mker > dat.txt");
        cout<<"Data Made"<<endl;
        cout<<"Running Mine"<<endl;
        t1 = GetCycleCount();
        system("./bzoj3626 < dat.txt > my.txt");
        t2 = GetCycleCount();
        cout<<"time used :: "<<(t2-t1)*1000/FREQUENCY<<"ms"<<endl;
        cout<<"Running std"<<endl;
        t1 = GetCycleCount();
        system("./bzoj3626std < dat.txt > std.txt");
        t2 = GetCycleCount();
        cout<<"time used :: "<<(t2-t1)*1000/FREQUENCY<<"ms"<<endl;
        cout<<"diffing answer"<<endl;
        if( system("diff my.txt std.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
    }
}