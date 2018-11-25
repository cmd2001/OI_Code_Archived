#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cstring>  
using namespace std;  
typedef long long LL;  
const int SIZEN=100010;  
class BIT{  
public:  
    int n;  
    int s[SIZEN];  
    #define lowbit(x) ((x)&(-x))  
    void clear(int _n){  
        n=_n;  
        memset(s,0,sizeof(s));  
    }  
    void modify(int x,int t){  
        for(;x<=n;x+=lowbit(x)) s[x]=max(s[x],t);  
    }  
    int pref_max(int x){  
        int ans=0;  
        for(;x;x-=lowbit(x)) ans=max(ans,s[x]);  
        return ans;  
    }  
};  
class Point{  
public:  
    LL x,y;  
    int id;  
};  
void print(const Point &p){  
    cout<<"("<<p.x<<","<<p.y<<" "<<p.id<<")";  
}  
bool operator < (const Point &a,const Point &b){  
    if(a.x==b.x) return a.y<b.y;  
    return a.x<b.x;  
}  
LL operator * (const Point &a,const Point &b){  
    return a.x*b.x+a.y*b.y;  
}  
int N;  
Point P[SIZEN];  
Point alpha1,alpha2;  
LL Y[SIZEN]={0};int tot=0;  
void coor_trans(void){//坐标变换  
    for(int i=0;i<=N;i++){  
        LL a=P[i].x*alpha2.y-alpha2.x*P[i].y;  
        LL b=alpha1.x*P[i].y-P[i].x*alpha1.y;  
        //LL b=alpha1.y*P[i].x-P[i].y*alpha1.x;  
        a*=-1,b*=-1;//强行改规则,只选x,y坐标都小于它的  
        P[i].x=a,P[i].y=b;  
        Y[tot++]=b;  
    }
    sort(Y,Y+tot);  
    tot=unique(Y,Y+tot)-Y;for(int i=0;i<=N;i++) P[i].y=lower_bound(Y,Y+tot,P[i].y)-Y+1;  
    sort(P,P+1+N); //for(int i=0;i<=N;i++) printf("%lld %lld\n",P[i].x,P[i].y);
    
}  
int dp[SIZEN]={0};  
BIT T;  
void work(void){  
    
    T.clear(N+1);  
    for(int i=0,j=0;i<=N;i++){  
        while(P[j].x<P[i].x){  
            T.modify(P[j].y,dp[P[j].id]);  
            j++;  
        }
        dp[P[i].id]=T.pref_max(P[i].y-1)+1;
        //if( dp[P[i].id] == 2 ) printf("dp = %d x = %d , y = %d\n",dp[P[i].id],P[i].x,P[i].y);
    }  
    printf("%d\n",dp[0]-1);  
}  
void read(void){  
    P[0].x=P[0].y=0;P[0].id=0;  
    scanf("%d",&N);  
    scanf("%I64d/%I64d",&alpha1.y,&alpha1.x);  
    scanf("%I64d/%I64d",&alpha2.y,&alpha2.x);  
    for(int i=1;i<=N;i++){  
        scanf("%I64d%I64d",&P[i].x,&P[i].y);  
        P[i].id=i;  
    }  
}  
int main(){  
    //freopen("t1.in","r",stdin);  
    read();  
    coor_trans();  
    work();  
    return 0;  
}  
