#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define ref(i,x,y)for(int i=x;i<=y;i++)
#define def(i,x,y)for(int i=x;i>=y;i--)
bool b[1030002];
int n,m,ansn,a[10002],ans[1000001];
short p[3]={10007,10917,30071};
short f[101][3];
char str[10002];
int mod(int x){
    int flag=0,len=strlen(str);
    if(str[0]=='-')flag=1,a[len]=0;
    a[0]=0;
    ref(i,flag,len-1)a[len-i]=str[i]-48;
    def(i,len,1)a[i-1]+=a[i]%x*10;
    if(!flag)return a[0]/10;else
        return(x-a[0]/10)%x;
}
bool judge(int x){
    ref(i,0,2){long long s=f[n][i];
        def(j,n-1,0)
            s=(s*x%p[i]+f[j][i])%p[i];
        if(s){
            while(x<m){x+=p[i];b[x]=1;}
            return 0;
        }
    }return 1;
}
int main()
{
    freopen("equation10.in","r",stdin);
    scanf("%d%d",&n,&m);
    ref(i,0,n){
        scanf("%s",str);
        ref(j,0,2)f[i][j]=mod(p[j]);
    }
    ref(i,1,m)if(!b[i])if(judge(i))
        ans[++ansn]=i;
    printf("%d\n",ansn);
    ref(i,1,ansn)printf("%d\n",ans[i]);
}
