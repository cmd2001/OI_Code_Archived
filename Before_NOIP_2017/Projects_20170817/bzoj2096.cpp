#include <cstdio>
#include <cstring>
#include <algorithm>
//by zrt
//problem:
using namespace std;
const int inf(0x3f3f3f3f) ;
const double eps(1e-10) ;
typedef long long LL;
int k,n;
int a[3000005];
struct N{
    int x,w; //pos val
    N(int a=0,int b=0){
        x=a,w=b;
    }
};
struct dddl{//维护最大值 --//单调递减 
    N q[3000005];
    int h,t;
    void clear(){ h=t=0; }
    void insert(N a){
        while(h!=t&&q[t-1].w<=a.w){t--;}
        q[t++]=a;
    }
    int get_val(){
        return q[h].w;
    }
    int get_pos(){
        return q[h].x;
    }
    void pop(int j){
        if(q[h].x==j) h++;
    }
}mx,mn;
int ans;
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    scanf("%d%d",&k,&n);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);}
    int j=1;//左端点指针 
//  mx.insert(N(1,a[1]));
//  mn.insert(N(1,a[1]));
    for(int i=1;i<=n;i++){
        mx.insert(N(i,a[i]));
        mn.insert(N(i,-a[i]));
        while(mx.get_val()+mn.get_val()>k) {
            mx.pop(j);mn.pop(j);j++;
        }
        ans=max(ans,i-j+1);
    }
    printf("%d\n",ans);
    return 0;
}