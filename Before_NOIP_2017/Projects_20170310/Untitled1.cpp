#include<bits/stdc++.h>
#define debug cout
using namespace std;
char in[20100*2],org[20100];
int cnt,torg[20100*2],s,e,ans[20100*2],maxr,pos;
inline int manacher()
{
    int ret=0;
    maxr=0,pos=0;
    for(int i=1;i<=cnt;i++)
    {
        if(i<maxr) ans[i]=min(ans[2*pos-i],maxr-i);
        else ans[i]=1;
        while(in[i+ans[i]]==in[i-ans[i]]&&i-ans[i]>=0) ans[i]++;
        --ans[i];
        if(i+ans[i]-1>maxr) maxr=i+ans[i]-1,pos=i;
        if(ans[i]>ret) ret=ans[i],s=torg[i-ans[i]+1],e=torg[i+ans[i]-1];
    }
    return ret;
}
inline void input()
{
    char c;
    int l=1;
    while((c=getchar())!=EOF) org[l++]=c;
    in[0]='#';
    for(int i=1;i<=l;i++) if((org[i]>='a'&&org[i]<='z')||(org[i]>='A'&&org[i]<='Z')) in[++cnt]=tolower(org[i]),torg[cnt]=i,in[++cnt]='#';
}
int main()
{
    input();
    printf("%d\n",manacher());
    for(int i=s;i<=e;i++) putchar(org[i]);
    putchar('\n');
    return 0;
}
