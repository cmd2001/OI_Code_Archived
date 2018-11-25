#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+10;
char s[maxn],t[maxn];
int nxt[maxn],ans[maxn];
void getnext()
{
    int len=strlen(t);
    int pos,maxr;
    nxt[0]=len;
    for(int i=0;i<len&&t[1]==t[i];i++) nxt[1]=i;
    pos=1,maxr=nxt[1];
    for(int i=2;i<len;i++)
    {
        int l=nxt[i-pos];
        if(i+l-1>=maxr)
        {
            int j=max(0,maxr-i);
            while(i+j<len&&t[i+j]==t[j]) j++;
            nxt[i]=j;
            pos=i,maxr=i+nxt[i];
        }
        else nxt[i]=l;
    }
}
void getext()
{
    int slen=strlen(s),tlen=strlen(t),minlen=min(slen,tlen);
    int pos,maxr;
    for(int i=0;i<minlen&&s[i]==t[i];i++) ans[0]=i;
    ans[0]++;
    pos=0,maxr=ans[0];
    debug<<ans[0]<<endl;
    for(int i=1;i<slen;i++)
    {
        int l=nxt[i-pos];
        if(i+l>=maxr)
        {
            int j=max(0,maxr-i);
            while(j<tlen&&i+j<slen&&s[i+j]==t[j]) j++;
            ans[i]=j;
            pos=i,maxr=i+ans[i];
        }
        else ans[i]=l;
    }
}
int main()
{
    scanf("%s",t);
    scanf("%s",s);
    getnext();
    getext();
    for(int i=0,l=strlen(t);i<l;i++) debug<<nxt[i]<<" ";
    debug<<endl;
    for(int i=0,l=strlen(s);i<l;i++) debug<<ans[i]<<" ";
    debug<<endl;
    return 0;
}
