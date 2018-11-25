//Cv6107_By_Cmd2001
#include<bits/stdc++.h>
using namespace std;
__int128_t dat[4],mx[4],in[4];
inline __int128_t getint()
{
    __int128_t ret=0,fix=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') fix=-1; ch=getchar();}
    while('0'<=ch&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret*fix;
}
inline void putint(__int128_t x)
{
    static char mem[150];
    int cnt=0;
    while(x)
    {
        mem[++cnt]=x%10+'0';
        x/=10;
    }
    if(!cnt) putchar('0');
    while(cnt) putchar(mem[cnt]),cnt--;
}
int main()
{
    int n;
    for(int i=1;i<=3;i++) mx[i]=dat[i]=getint();
    scanf("%d",&n);
    while(n--) for(int i=1;i<=3;i++) mx[i]=max(mx[i],getint());
    for(int i=1;i<=3;i++)
    {
        putint(mx[i]-dat[i]);
        putchar(' ');
    }
}
