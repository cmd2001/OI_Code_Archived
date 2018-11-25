#include<bits/stdc++.h>
using namespace std;

char a[100],b[100];
FILE *my,*stdf;

int main() {
    my = fopen("my.txt","r");
    stdf = fopen("std.txt","r");
    const int lim = 100000;
    for(int i=1;i<=lim;i++) {
        fscanf(my,"%s",a) , fscanf(stdf,"%s",b);
        if( string(a) != string(b) ) printf("%d\n",i) , exit(0);
    }
}
