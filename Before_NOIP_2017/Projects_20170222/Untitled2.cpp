#include<bits/stdc++.h>
using namespace std;
char mid[30],pos[30];
void solve(char *a,char *b,int x)
{
    int i=0;
    printf("%c",*(b+x-1));
    while(*(a+i)!=*(b+x-1)) ++i;
    if(i>0) solve(a,b,i);
    if(i<x-1) solve(a+i+1,b+i,x-i-1);
}
int main()
{
    scanf("%s%s",mid,pos);
    solve(mid,pos,strlen(pos));
    return 0;
}
