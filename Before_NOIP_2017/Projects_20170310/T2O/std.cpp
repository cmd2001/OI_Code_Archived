#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10,maxl=1e6+10;
int n,l[maxn],r[maxn],ans[maxl*2],cnt,len=1,maxr,pos,s,e;
char in[maxl],dat[maxl*2];
inline int manacher()
{
    int ret=0;
    maxr=0,pos=0;
    for(int i=1;i<=cnt;i++)
    {
        if(i<maxr) ans[i]=min(ans[2*pos-i],maxr-i);
        else ans[i]=1;
        while(dat[i+ans[i]]==dat[i-ans[i]]&&i-ans[i]>=0) ans[i]++;
        --ans[i];
        if(i+ans[i]-1>maxr) maxr=i+ans[i]-1,pos=i;
        if(ans[i])
        {
            int a=(i-ans[i]+2)/2,b=(i+ans[i])/2;
            int x=lower_bound(l+1,l+n,a)-l,y=lower_bound(r+1,r+n,b)-r;
            if(r[y]!=b) y--;
            if(y-x+1>ret)
            {
                ret=y-x+1;
                s=a,e=b;
            }
        }
    }
    return ret;
}
inline void convert()
{
    --len;
    dat[0]='#';
    for(int i=1;i<=len;i++)
    {
        dat[++cnt]=in[i];
        dat[++cnt]='#';
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",in+len);
        l[i]=len;
        len=strlen(in+1);
        r[i]=len++;
    }
    convert();
    printf("%d\n",manacher());
    for(int i=s;i<=e;i++) putchar(in[i]);
    return 0;
}
