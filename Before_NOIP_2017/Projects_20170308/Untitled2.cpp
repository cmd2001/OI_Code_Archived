#include<bits/stdc++.h>
#define debug cout
using namespace std;
char in[210],cnt;
int ans[210];
int maxr,pos;
int manacher()
{
    int ret=0;
    maxr=0,pos=0;
    for(int i=1;i<=cnt;i++)
    {
        if(i<maxr) ans[i]=min(ans[2*pos-i],maxr-i);
        else ans[i]=1;
        while(in[i+ans[i]]==in[i-ans[i]]&&i-ans[i]>=0) ans[i]++;
        --ans[i];
        //debug<<"i="<<i<<"ans="<<ans[i]<<endl;
        if(i+ans[i]-1>maxr) maxr=i+ans[i]-1,pos=i;
        ret=max(ret,ans[i]);
    }
    return ret;
}
void input()
{
    char c;
    in[0]='#';
    while((c=getchar())!='\n') in[++cnt]=c,in[++cnt]='#';
    //for(int i=1;i<=cnt;i++) debug<<in[i];
    //debug<<endl;
}
int main()
{
    input();
    cout<<manacher()<<endl;
    return 0;
}
