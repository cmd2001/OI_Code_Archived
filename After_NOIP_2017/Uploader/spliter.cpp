#include<bits/stdc++.h>
#define debug cout
using namespace std;
FILE *sou = fopen("dat.wa2.txt","r");
FILE *dat=fopen("dat.txt","w");
//Please replace __problem_name__ with your problem name.

inline void split_case() {
    int n,x;
    fscanf(sou,"%d",&n);
    fprintf(dat,"1\n%d\n",n);
    while(n--) {
        fscanf(sou,"%d",&x) , fprintf(dat,"%d%c",x,n?' ':'\n');
    }
    fclose(dat);
}

int main() {
    int T;
    fscanf(sou,"%d",&T);
    for(int i=1;i<=T;i++) {
        printf("Case :: %d\n",i);
        split_case();
        fclose(dat);
        system("__problem_name__.exe < dat.txt > my.txt");
        system("__problem_name__std.exe < dat.txt > std.txt");
        if( system("fc my.txt std.txt") ) {
            puts("============WA============");
            getchar();getchar();
        }
    }
}
