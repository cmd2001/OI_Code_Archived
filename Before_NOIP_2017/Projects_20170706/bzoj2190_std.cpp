#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int N,ans;
int p[80000],phi[80000],prime[80000];
inline void getphi(){
    phi[1]=1;
    for (int i=2;i<=N;++i){
        if (!p[i]){
            prime[++prime[0]]=i;
            phi[i]=i-1;
        }
        for (int j=1;j<=prime[0]&&i*prime[j]<=N;++j){
            p[i*prime[j]]=1;
            if (i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            else phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
int main(){
    scanf("%d",&N);
    if (N==1) {printf("1\n"); return 0;}
    if (N==2) {printf("3\n"); return 0;}
    getphi();
    for (int i=2;i<N;++i)
      ans+=phi[i];
    ans*=2;
    ans+=3;
    printf("%d\n",ans); 
}
