#include<iostream>  
#include<cstdio>  
#define N 10000005  
#define ll long long   
#define debug cout
using namespace std;  
   
int n,m,cnt,a[N],b[N],c[N],g[N];  
void pfs(){  
    int i,j,k; g[1]=0;  
    for (i=2; i<=10000000; i++){  
        if (!a[i]){  
            c[++cnt]=i; a[i]=g[i]=1; b[i]=i;  
        }  
        for (j=1; j<=cnt; j++){  
            k=i*c[j]; if (k>10000000) break;  
            if (i%c[j]){  
                a[k]=1; b[k]=c[j];  
                g[k]=(a[i]==1)?-g[i]:0;  
            } else{
            	/*if( k == 4 )
            		debug<<"k == 4"<<endl;*/
                a[k]=a[i]+1; b[k]=b[i]*c[j];  
                int tmp=i/b[i];  
                /*if( k == 4 )
                	debug<<"tmp  "<<tmp<<endl;*/
                if (tmp==1) g[k]=1; else g[k]=(a[tmp]==a[k])?-g[tmp]:0;  
                break;  
            }  
        }  
    }  
    //for (i=2; i<=10000000; i++) g[i]+=g[i-1];  
}  
int main(){  
	pfs();
	for(int i=1;i<=10;i++) debug<<g[i]<<" ";debug<<endl;
    int cas; scanf("%d",&cas);  
    while (cas--){  
        scanf("%d%d",&m,&n); int i,j; ll ans=0;  
        for (i=1; i<=m && i<=n; i=j+1){  
            j=min((m/(m/i)),n/(n/i));  
            ans+=(ll)(g[j]-g[i-1])*(m/i)*(n/i);  
        }  
        printf("%lld\n",ans);  
    }  
    return 0;  
}  
