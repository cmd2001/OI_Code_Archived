#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;

char com[maxn];

int main() {
    for(int i=1;i<=20;i++) sprintf(com,"./regen konomi%d.in konomi%d.out %d.in",i,i,i) , system(com);
    return 0;
}
