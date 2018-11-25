#include<bits/stdc++.h>
#define debug cerr
using namespace std;
const int ns[]={0,
    3,3,10,100,100,
    100,100,100,100,5000,
    5000,300,300,5000,5000,
    50000,50000,50000,50000,50000,
    100000,100000,100000,100000,100000};
const int ms[]={0,
    300000,300000,10,150000,150000,
    150000,10,10,10,150000,
    150000,300,300,5000,5000,
    50000,50000,50000,50000,50000,
    150000,150000,150000,150000,150000};
const int ts[]={0,
    0,1,0,0,0,
    0,1,1,1,0,
    0,1,1,1,1,
    0,0,1,1,1,
    0,0,1,1,1
};

int main() {
    static char com[1010];
    for(int i=1;i<=25;i++) {
        debug<<"Making Case :: "<<i<<endl;
        freopen("communi.txt","w",stdout) , printf("%d %d %d\n",ns[i],ms[i],ts[i]) , fclose(stdout);
        sprintf(com,"./T2mker < communi.txt > %d.in",i) , system(com);
        debug<<"Input Data Made"<<endl;
        sprintf(com,"./T2 < %d.in > %d.out",i,i) , system(com);
        debug<<"Output Data Made"<<endl;
    }
    return 0;
}
