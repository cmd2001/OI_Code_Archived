#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int in[maxn],n,k;

struct que
{
    int dat[maxn],p[maxn],s,e;

    inline void cl()
    {
        for(int i=0;i<=e;i++) dat[i]=0;
        s=e=0;
        dat[0]=-0x3f3f3f3f;
    }

    inline void push(int x,int pos)
    {
        while(s<=e&&dat[s]<=x) s++;
        while(s<=e&&dat[e]<=x) e--;
        dat[++e]=x;
        p[e]=pos;
    }
    inline int get(int pos)
    {
        while(s<e&&p[s]<=pos-k) s++;
        return dat[s];
    }
}q;


int main()
{
    scanf("%d%d",&n,&k);

    for(int i=1;i<=n;i++) scanf("%d",in+i);

    q.cl();
    for(int i=1;i<k;i++) q.push(-in[i],i);
    for(int i=k;i<=n;i++)
    {
        q.push(-in[i],i);
        //q.print(i);
        printf("%d ",-q.get(i));
    }
    putchar('\n');

    q.cl();
    for(int i=1;i<k;i++) q.push(in[i],i);
    for(int i=k;i<=n;i++)
    {
        q.push(in[i],i);
        //q.print(i);
        printf("%d ",q.get(i));
    }
    putchar('\n');

    return 0;
}
