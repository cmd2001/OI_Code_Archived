#include<bits/stdc++.h>
using namespace std;

char com[1024];

int main() {
    for(int i=1;i<=20;i++) {
        cerr<<"Solving Case ::"<<i<<endl;
        sprintf(com,"cp bangeki%02d.in %d.in",i,i) , system(com);
        sprintf(com,"cp bangeki%02d.ans %d.out",i,i) , system(com);
    }
}