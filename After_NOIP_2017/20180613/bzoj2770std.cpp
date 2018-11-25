#include<cstdio>  
#include<cstdlib>  
#include<algorithm>  
#include<map>  
using namespace std;  
typedef long long ll;  
    
inline char nc()  
{  
    static char buf[100000],*p1=buf,*p2=buf;  
    if (p1==p2) { p2=(p1=buf)+fread(buf,1,100000,stdin); if (p1==p2) return EOF; }  
    return *p1++;  
}  
    
inline void read(int &x)  
{  
    char c=nc(),b=1;  
    for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;  
    for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;  
}  
    
inline void read(char &x)  
{  
    for (x=nc();!(x>='A' && x<='Z');x=nc());  
}  
    
const int N=400005;  
    
namespace SEG{  
    ll val[N];  
    int T[N<<2];  
    int M;  
    inline int Min(int x,int y){  
        return val[x]<val[y]?x:y;  
    }  
    inline void Build(int n){  
        for (M=1;M<n+2;M<<=1);  
        val[0]=1LL<<60;  
        for (int i=1;i<=n;i++)  
            T[i+M]=i,val[i]=1LL<<60;  
        for (int i=M-1;i;i--)  
            T[i]=Min(T[i<<1],T[i<<1|1]);  
    }  
    inline void Modify(int s,ll r){  
        val[s]=r; s+=M;   
        while (s>>=1)  
            T[s]=Min(T[s<<1],T[s<<1|1]);  
    }  
    inline int Query(int s,int t){  
        int ret=0;  
        for (s+=M-1,t+=M+1;s^t^1;s>>=1,t>>=1){  
            if (~s&1) ret=Min(ret,T[s^1]);  
            if ( t&1) ret=Min(ret,T[t^1]);  
        }  
        return ret;  
    }  
}  
    
int sx[N],icnt;  
inline int Bin(int x){  
    return lower_bound(sx+1,sx+icnt+1,x)-sx;  
}  
    
struct event{  
    int f,a,b;  
    void read(){  
        char order; ::read(order);  
        if (order=='I') f=1,::read(a),::read(b),sx[++icnt]=a;  
        if (order=='D') f=2,::read(a);  
        if (order=='Q') f=3,::read(a),::read(b);  
    }  
}eve[N];  
int tot;  
    
int n,m;  
    
int main()  
{  
    using namespace SEG;  
    int key,key2,pri;   
    read(n); read(m);  
    for (int i=1;i<=n;i++) read(eve[i].a),eve[i].f=1,sx[++icnt]=eve[i].a;  
    for (int i=1;i<=n;i++) read(eve[i].b);  
    tot=n;  
    for (int i=1;i<=m;i++)   
        eve[++tot].read();  
    sort(sx+1,sx+icnt+1);  
    icnt=unique(sx+1,sx+icnt+1)-sx-1;  
    Build(icnt);  
    for (int i=1;i<=tot;i++)  
    {  
        if (eve[i].f==1)  
        {  
            key=Bin(eve[i].a); pri=eve[i].b;  
            Modify(key,pri);  
        }  
        else if (eve[i].f==2)  
        {  
            key=Bin(eve[i].a);  
            Modify(key,1LL<<60);  
        }  
        else  
        {  
            key=Bin(eve[i].a);  
            key2=Bin(eve[i].b);  
            if (key>key2) swap(key,key2);  
            pri=sx[Query(key,key2)];  
            printf("%d\n",pri);  
        }  
    }  
    return 0;  
}  