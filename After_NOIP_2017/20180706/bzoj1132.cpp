#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=3e3+1e2;

struct Point {
    int x,y;
    friend Point operator + (const Point &a,const Point &b) {
        return (Point){a.x+b.x,a.y+b.y};
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend lli operator * (const Point &a,const Point &b) {
        return (lli) a.x * b.y - (lli) a.y * b.x;
    }
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}in[maxn],ps[maxn];

bool cmp(const Point &a,const Point &b) {
    return a * b ? a * b > 0 : a.x < b.x;
}

int n;
lli ans;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&in[i].x,&in[i].y);
    std::sort(in+1,in+1+n);
    for(int i=1,top=0;i<=n-2;i++,top=0) {
        for(int j=i+1;j<=n;j++) ps[++top] = in[j] - in[i];
        std::sort(ps+1,ps+1+top,cmp); Point prf = (Point){0,0};
        for(int j=1;j<=top;j++) ans += prf * ps[j] , prf = prf + ps[j];
    }
    printf("%lld",ans>>1) , puts(ans&1?".5":".0");
    return 0;
}

