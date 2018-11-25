#include<bits/stdc++.h>
#define debug cout
using namespace std;
FILE *sou = fopen("dat.wa.txt","r");
FILE *dat=fopen("dat.txt","w");
//Please replace __problem_name__ with your problem name.

inline void split_case(int i) {
    if( i % 1000 == 1 ) {
        fclose(dat);
        system("del dat.txt");
        dat=fopen("dat.txt","w");
        fprintf(dat,"1000\n");
    }
    int n,x;
    fscanf(sou,"%d",&n);
    fprintf(dat,"%d\n",n);
    while(n--) {
        fscanf(sou,"%d",&x) , fprintf(dat,"%d%c",x,n?' ':'\n');
    }
}
int main() {
    int T;
    fscanf(sou,"%d",&T);
    for(int i=1;i<=T;i++) {
        if( i % 1000 == 0 ) printf("Spliting Case :: %d\n",i);
        split_case(i);
        if( i % 1000 == 0 ) {
            fclose(dat);
            system("__problem_name__.exe < dat.txt > my.txt");
            system("__problem_name__std.exe < dat.txt > std.txt");
            if( system("fc my.txt std.txt") ) {
                puts("============WA============");
                getchar();getchar();
            }
        }
    }
}
