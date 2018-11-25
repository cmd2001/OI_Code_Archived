#include <iostream>  
#include<stdio.h>  
#include<algorithm>  
#include<math.h>  
#include<cstring>  
using namespace std;  
const int MAX=2*1e4+20;  
int N;  
int y[MAX];  
int sum=0;  
typedef struct{  
    int x,y1,y2;  
    int f;  
    void set(int xx,int yy1,int yy2,int ff)  
    {  
        x=xx;  
        y1=yy1;  
        y2=yy2;  
        f=ff;  
    }  
}Node;  
Node no[MAX];  
typedef struct  
{  
    int left,right;  
    int cover;  
    int realleft,realright,len;  
    int lflag,rflag,cnt;  
    void set(int l,int r)  
    {  
        lflag=rflag=cnt=0;  
        left=l;  
        right=r;  
        cover=0;  
        len=0;  
        realleft=y[l];  
        realright=y[r];  
    }  
}P;  
P per[4*MAX];  
bool cmp(const Node &n1,const Node &n2)  
{  
    if(n1.x!=n2.x)  
        return n1.x<n2.x;  
    else  
        return n1.f>n2.f;  
}  
void build(int id,int left,int right)  
{  
    per[id].set(left,right);  
    if(right-left==1)  
        return;  
    int mid=(left+right)/2;  
    build(id<<1,left,mid);  
    build(id<<1|1,mid,right);  
}  
void get_len(int t)  
{  
    if(per[t].cover>0)  
    {  
        per[t].len=per[t].realright-per[t].realleft;  
        per[t].cnt=per[t].lflag=per[t].rflag=1;  
    }  
    else  
        if(per[t].left+1==per[t].right)  
        {  
            per[t].len=0;  
            per[t].cnt=per[t].lflag=per[t].rflag=0;  
        }  
    else  
        {  
            per[t].len=per[t<<1].len+per[t<<1|1].len;  
            per[t].lflag=per[t<<1].lflag;  
            per[t].rflag=per[t<<1|1].rflag;  
            per[t].cnt=per[t<<1].cnt+per[t<<1|1].cnt-per[t<<1].rflag*per[t<<1|1].lflag;  
        }  
}  
void update(int id,Node node)  
{  
    if(per[id].realleft==node.y1&&per[id].realright==node.y2)  
    {  
        per[id].cover+=node.f;  
        get_len(id);  
        return;  
    }  
        if(per[id<<1].realright>=node.y2)  
            update(id<<1,node);  
        else  
            if(per[id<<1|1].realleft<=node.y1)  
            update(id<<1|1,node);  
        else  
        {  
            Node m=node;  
            m.y2=per[id<<1].realright;  
            update(id<<1,m);  
            m=node;  
            m.y1=per[id<<1|1].realleft;  
            update(id<<1|1,m);  
        }  
        get_len(id);  
  
}  
int main()  
{  
  
    int x1,x2,y1,y2;  
    int num=1;  
    while(scanf("%d",&N)!=EOF)  
    {  
        memset(y,0,sizeof(y));  
        sum=0;  
        int t=0;  
        for(int i=0;i<N;i++)  
        {  
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);  
            no[t].set(x1,y1,y2,1);  
            y[t]=y1;  
            t++;  
            no[t].set(x2,y1,y2,-1);  
            y[t]=y2;  
            t++;  
        }  
        sort(no,no+t,cmp);  
        sort(y,y+t);  
        int le=0;  
        y[le++]=y[0];  
        for(int i=1;i<t;i++)  
            if(y[i]!=y[i-1])  
            y[le++]=y[i];  
        build(1,0,le-1);  
        int d=0;  
        for(int i=0;i<t-1;i++)  
        {  
            update(1,no[i]);  
            sum+=abs(per[1].len-d);  
            d=per[1].len;  
            sum+=2*per[1].cnt*( no[i+1].x-no[i].x);  
        }  
        update(1,no[t-1]);  
        sum+=abs(per[1].len-d);  
        cout<<sum<<endl;  
    }  
    return 0;  
}  
