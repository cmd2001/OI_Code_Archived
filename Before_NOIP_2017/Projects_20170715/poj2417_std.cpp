#include<iostream>
#include <cstdio>
#include <cmath>
#include <map>
#define debug cout
using namespace std;
typedef long long ll;
ll p,b,n;

void exgcd(ll c,ll d,ll &x,ll &y){
    if(!d){
        x=1;y=0;
        return ;
    }
    exgcd(d,c%d,x,y);
    ll xx=y,yy=x-(c/d)*y;
    x=xx;y=yy;
}

void work(){
    ll m=(ll)sqrt(p),bb=1,nn=n,inv,t;
    map<int,int> num;
    map<int,bool> app;

    app[1]=1;
    num[1]=0;
    for(int i=1;i<=m-1;i++){
        bb=bb*b%p;
        if(!app[bb]){
            app[bb]=1;
            num[bb]=i;
        }
    }
    bb=bb*b%p;
    exgcd(bb,p,inv,t);
    if(inv>0) inv%=p;
    else inv=inv%p+p;
    debug<<"rev="<<inv<<endl;
    for(int i=0;i<=m;i++){
    	debug<<"i="<<i<<"nn="<<nn<<endl;
        if(app[nn]){
            printf("%lld\n",i*m+num[nn]);
            return ;
        }
        nn=nn*inv%p;
    }
    printf("no solution\n");
}

int main(){
    while(scanf("%lld%lld%lld",&p,&b,&n)!=EOF) work();

    return 0;
}
