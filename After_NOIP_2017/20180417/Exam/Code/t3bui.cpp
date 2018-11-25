#include<bits/stdc++.h>

char fs[100];

int main() {
    for(int i=0;i<10;i++) {
        sprintf(fs,"shortest%d.out",i);
        freopen(fs,"w",stdout);
        puts("0");
        fclose(stdout);
    }
}
