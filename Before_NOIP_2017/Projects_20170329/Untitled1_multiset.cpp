#include<bits/stdc++.h>
#define debug cout
#define maxn 300100
using namespace std;
struct solution
{
    multiset<int> s;
    int lson[maxn],rson[maxn],dat[maxn],fa[maxn],add[maxn],dis[maxn];
    int fix;
    int findroot(int x)
    {
        while(fa[x]) x=fa[x];
        return x;
    }
    void push(int x)
    {
    	if(!add[x]) return;
        if(lson[x]) add[lson[x]]+=add[x],dat[lson[x]]+=add[x];
        if(rson[x]) add[rson[x]]+=add[x],dat[rson[x]]+=add[x];
        add[x]=0;
    }
    void merge(int x,int y)
    {
        push(x);push(y);
        if(!rson[x]) {rson[x]=y;fa[y]=x;}
        else if(rson[x]&&dat[rson[x]]>=dat[y]) merge(rson[x],y);
        else if(rson[x]&&dat[rson[x]]<dat[y]) {merge(y,rson[x]);rson[x]=y;fa[y]=x;}
        if(dis[rson[x]]>dis[lson[x]]) swap(lson[x],rson[x]);
        dis[x]=dis[rson[x]]+1;
        return;
    }
    int del(int x)
    {
        int &p=fa[x],l=lson[x],r=rson[x];
        int *pos=(lson[fa[x]]==x?&lson[fa[x]]:&rson[fa[x]]);
        push(x);
        if((!l)||(!r)) *pos=(l|r);
        else if(dat[l]>=dat[r]) {*pos=l;merge(l,r);}
        else {*pos=r;merge(r,l);}
        fa[*pos]=p;
        p=0;
        lson[x]=rson[x]=0;
        return *pos;
    }
    void updatetree(int x,int val)
    {
        x=findroot(x);
        if(*s.find(dat[x])==dat[x]) {s.erase(s.find(dat[x]));/*debug<<"erased"<<dat[x]<<endl;*/}
        //else debug<<"notfind@48"<<"dat="<<dat[x]<<endl;
        dat[x]+=val;
        add[x]+=val;
        s.insert(dat[x]);
        //debug<<"inserted"<<dat[x]<<endl;
    }
    void pushup(int x)
    {
    	if(fa[x]) pushup(fa[x]);
    	push(x);
    }
    void updatenode(int x,int val)
    {
        int pos=findroot(x);
        pushup(x);
        if(pos==x)
        {
        	if(!(lson[x]||rson[x])) 
			{
				if(*s.find(dat[x])==dat[x]) {s.erase(s.find(dat[x]));/*debug<<"erased"<<dat[x]<<endl;*/}
				dat[x]+=val;
				s.insert(dat[x]);
            	//debug<<"inserted"<<dat[x]<<endl;
            	return;
			}
        	//debug<<"pos===============================x"<<endl;
            //debug<<"pos="<<pos<<endl;
            push(x);
            if(*s.find(dat[x])==dat[x]) {s.erase(s.find(dat[x]));/*debug<<"erased"<<dat[x]<<endl;*/}
            else debug<<"notfind@66"<<"dat="<<dat[x]<<endl;
            int npos=del(x);
            //debug<<"npos="<<npos<<endl;
            lson[0]=rson[0]=0;
            fa[npos]=0;
            s.insert(dat[npos]);
            //debug<<"inserted"<<dat[pos]<<endl;
            pos=npos;
        }
        else
        {
            push(x);
            del(x);
        }
        dat[x]+=val;
        if(dat[x]>=dat[pos])
        {
            if(*s.find(dat[pos])==dat[pos]) {s.erase(s.find(dat[pos]));/*debug<<"erased"<<dat[pos]<<endl;*/}
            //else debug<<"notfind@83"<<"dat="<<dat[pos]<<endl;
            fa[pos]=x;
            merge(x,pos);
            s.insert(dat[x]);
            //debug<<"inserted"<<dat[x]<<endl;
        }
        else {fa[x]=pos;merge(pos,x);}
    }
    int query(int x)
    {
        int ret=dat[x];
        x=fa[x];
        while(x) ret+=add[x],x=fa[x];
        return ret;
    }
}pro;
int main()
{
    freopen("1.in","r",stdin);
    freopen("my.out","w",stdout);
	pro.dis[0]=-1;
	pro.fix=0;
    int n,q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&pro.dat[i]);
        pro.s.insert(pro.dat[i]);
        //debug<<"inserted"<<pro.dat[i]<<endl;
    }
    char cmd[5];
    scanf("%d",&q);
    for(int i=1,x,y;i<=q;i++)
    {
    	//debug<<"d60="<<pro.dat[60]<<endl;
    	//debug<<"i="<<i<<endl;
        scanf("%s",cmd);
        if(cmd[0]=='U')
        {
            scanf("%d%d",&x,&y);
            x=pro.findroot(x),y=pro.findroot(y);
			if(x==y) continue;
            //debug<<"fax="<<x<<"fay="<<y<<endl;
            //debug<<"dx="<<pro.dat[x]<<"dy="<<pro.dat[y]<<endl;
            if(pro.dat[x]>=pro.dat[y])
            {
                //pro.fa[y]=x;
                if(*pro.s.find(pro.dat[y])==pro.dat[y]) {pro.s.erase(pro.s.find(pro.dat[y]));/*debug<<"erased"<<pro.dat[y]<<endl;*/}
                //else debug<<"notfind@124"<<"dat="<<pro.dat[y]<<endl;
                pro.merge(x,y);
            }
            else
            {
                //pro.fa[x]=y;
                if(*pro.s.find(pro.dat[x])==pro.dat[x]) {pro.s.erase(pro.s.find(pro.dat[x]));/*debug<<"erased"<<pro.dat[x]<<endl;*/}
                //else debug<<"notfind@130"<<"dat="<<pro.dat[x]<<endl;
                pro.merge(y,x);
            }
        }
        else if(cmd[0]=='A')
        {
            scanf("%d",&x);
            if(cmd[1]=='1') {scanf("%d",&y);pro.updatenode(x,y);}
            else if(cmd[1]=='2') {scanf("%d",&y);pro.updatetree(x,y);}
            else if(cmd[1]=='3') pro.fix+=x;
        }
        else if(cmd[0]=='F')
        {
            if(cmd[1]=='1') scanf("%d",&x),printf("%d\n",pro.query(x)+pro.fix);
            else if(cmd[1]=='3') printf("%d\n",*pro.s.rbegin()+pro.fix);
            else if(cmd[1]=='2') scanf("%d",&x),printf("%d\n",pro.dat[pro.findroot(x)]+pro.fix);
        }
    }
    return 0;
}
