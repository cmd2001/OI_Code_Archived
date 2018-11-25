#include<cstdio>
using namespace std;

#define int long long
int H[17],P[300],X[300],tot;
inline void add(int x,int y){
    P[++tot]=y;X[tot]=H[x];H[x]=tot;
}
void find(int p,int x,int now,int t){
    if(x==5) add(p,t);
    if(x>4) return ;
    if((now&1)==0) find(p,x+1,now>>1,t+(1<<(x-1)));
    if((now&3)==0) find(p,x+2,now>>2,t);
    if((now&1)!=0) find(p,x+1,now>>1,t);
}
int n,m;
inline void mul(int a[][16],int b[][16]){
    int c[16][16]={0};
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            for(int k=0;k<16;k++){
                c[i][j]+=a[i][k]*b[k][j];
                if(c[i][j]>=m) c[i][j]%=m;
            }
        }
    }
    for(int i=0;i<16;i++) for(int j=0;j<16;j++) a[i][j]=c[i][j];
}
int f[16][16];
int p[16][16];
signed main(){freopen("count.in","r",stdin);freopen("count.out","w",stdout);
    for(int i=0;i<1<<4;i++){
        find(i,1,i,0);
    }
    
    for(int i=0;i<1<<4;i++){
        for(int j=H[i];j;j=X[j]){
            f[i][P[j]]=1;
        }
    }
    while(scanf("%lld%lld",&n,&m)&&n){
        int t[16][16]={0};
        t[0][0]=1;
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                p[i][j]=f[i][j];
            }
        }
        while(n){
            if(n&1) mul(t,p);
            mul(p,p);
            n>>=1; 
        }
        printf("%lld\n",t[0][0]);
    }
    
    return 0;
}