#include<bits/stdc++.h>
using namespace std;
int a[10],b[10],c[10],d[10],e[10],f[10];
int n,m;
int main()
{
    freopen("count.in","r",stdin);
   freopen("count.out","w",stdout);
    while(cin>>n>>m){
        if(n==0&&m==0) {
            return 0;
        }
        memset(a,0,sizeof(a));
         memset(b,0,sizeof(a));
          memset(c,0,sizeof(a));
           memset(d,0,sizeof(a));
            memset(e,0,sizeof(a));
             memset(f,0,sizeof(a));
        a[1]=1;
    b[1]=1;
     c[1]=1;
    e[1]=1;
     f[1]=1;
    int now=0;
  for(int i=2;i<=n;i++)
  {
  		a[now]=b[now^1];
  		b[now]=a[now^1]+b[now^1]+c[now^1]+e[now^1]+f[now^1];
  		c[now]=b[now^1]+d[now^1];
		f[now]=b[now^1]+e[now^1];
  		d[now]=c[now^1];
  		e[now]=f[now^1]+b[now^1];
  		a[now]%=m;
  		b[now]%=m;
  		c[now]%=m;
  		d[now]%=m;
  		e[now]%=m;
  		f[now]%=m;
  		now=(now^1);
  }
  cout<<b[now^1]%m<<endl;
    }
  

}
