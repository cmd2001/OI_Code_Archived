#include<bits/stdc++.h>
using namespace std;

char com[1024];

/*int main() {
    for(int i=1;i<=20;i++) {
        cerr<<"Solving Case ::"<<i<<endl;
        sprintf(com,"./T1 < bangeki%02d.in > bangeki%02d.ans",i,i) , 
        system(com);
    }
}*/

int main() {
    for(int i=1;i<=20;i++) {
        cerr<<"Solving Case ::"<<i<<endl;
        sprintf(com,"./T3 < %d.in > %d.out",i,i) , 
        system(com);
    }
}