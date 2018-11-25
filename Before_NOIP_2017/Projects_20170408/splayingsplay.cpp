#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=100100;
int lson[maxn],rson[maxn],fa[maxn],dat[maxn],siz[maxn],num[maxn];
int root,cnt;
void splay(int x);
void zig(int x)
{
    //debug<<"zig\n";
    const int gfa=fa[x],son=lson[x];
    fa[son]=gfa;
    if(gfa)
    {
        if(lson[gfa]==x) lson[gfa]=son;
        else rson[gfa]=son;
    }
    else root=son;
    lson[x]=rson[son];
    if(rson[son]) fa[rson[son]]=x;
    fa[x]=son;
    rson[son]=x;
    siz[son]=siz[x];
    siz[x]=siz[lson[x]]+siz[rson[x]]+num[x];
}
void zag(int x)
{
    //debug<<"zag\n";
    const int gfa=fa[x],son=rson[x];
    fa[son]=gfa;
    if(gfa)
    {
        if(lson[gfa]==x) lson[gfa]=son;
        else rson[gfa]=son;
    }
    else root=son;
    rson[x]=lson[son];
    if(lson[son]) fa[lson[son]]=x;
    fa[x]=son;
    lson[son]=x;
    siz[son]=siz[x];
    siz[x]=siz[lson[x]]+siz[rson[x]]+num[x];
}
void insert(int x)
{
	//debug<<"inserting"<<x<<endl;
    int pos=root;
    while(1)
    {
        siz[pos]++;
        if(x==dat[pos])
        {
            num[pos]++;
            return;
        }
        if(x<dat[pos])
        {
            if(lson[pos]) pos=lson[pos];
            else
            {
                lson[pos]=++cnt;
                dat[cnt]=x;
                fa[cnt]=pos;
                //debug<<"cnt="<<cnt<<fa[cnt]<<endl;
                siz[cnt]=num[cnt]=1;
                splay(cnt);
                return;
            }
        }
        else
        {
            if(rson[pos]) pos=rson[pos];
            else
            {
                rson[pos]=++cnt;
                dat[cnt]=x;
                fa[cnt]=pos;
                siz[cnt]=num[cnt]=1;
                splay(cnt);
                return;
            }
        }
    }
}
int query(int x)//find a node whose dat == x, return a number of the pos, 0 means not found.
{
    int pos=root;
    while(pos&&x!=dat[pos]) pos=(x<dat[pos]?lson[pos]:rson[pos]);
    if(pos) splay(pos);
    return pos;
}
void splay(int x)
{
	//debug<<"splaying"<<x<<"\n";
    if(x==root) return;
    int ffa,gfa;
    while(x!=root)
    {
        ffa=fa[x],gfa=fa[fa[x]];
        if(gfa)
        {
                 if(x==lson[ffa]&&ffa==lson[gfa]) {zig(fa[x]);zig(fa[x]);}
            else if(x==lson[ffa]&&ffa==rson[gfa]) {zig(fa[x]);zag(fa[x]);}
            else if(x==rson[ffa]&&ffa==lson[gfa]) {zag(fa[x]);zig(fa[x]);}
            else if(x==rson[ffa]&&ffa==rson[gfa]) {zag(fa[x]);zag(fa[x]);}
        }
        else
        {
            if(ffa!=root){debug<<"x="<<x<<"ffa="<<ffa<<"root="<<root<<"\n"<<"!gfa&&ffa!=root"<<"\n"<<"cnt="<<cnt<<endl;exit(0);}
                 if(x==lson[ffa]) zig(fa[x]);
            else if(x==rson[ffa]) zag(fa[x]);
        }
    }
}
void eatnode(int a,int b)
{
    if(b!=rson[a])
    {
        if(lson[b]) {debug<<"bug\n";exit(0);}
        if(rson[b]) fa[rson[b]]=fa[b];
        if(b==lson[fa[b]]) lson[fa[b]]=rson[b];
        else rson[fa[a]]=rson[b];
        lson[b]=lson[a],rson[b]=rson[a];
        if(lson[a]) fa[lson[a]]=b;
        if(rson[a]) fa[rson[a]]=b;
        siz[b]=siz[lson[b]]+siz[rson[b]]+num[b];
        fa[b]=fa[a];
        if(a!=root)
        {
            /*debug<<"a!=root"<<endl;
            debug<<"fa[a]="<<fa[a]<<endl;
            debug<<lson[fa[a]]<<rson[fa[a]]<<endl;*/
            if(a==lson[fa[a]]) lson[fa[a]]=b;
            else rson[fa[a]]=b;
            siz[fa[b]]=siz[lson[fa[b]]]+siz[rson[fa[b]]]+num[b];
        }
        else root=b;
    }
    else
    {
        //debug<<"b==rosn[a]"<<endl;
        fa[b]=fa[a];
        lson[b]=lson[a];
        if(lson[a]) fa[lson[a]]=b;
        if(a!=root)
        {
            /*debug<<"a!=root"<<endl;
            debug<<"fa[a]="<<fa[a]<<endl;
            debug<<lson[fa[a]]<<rson[fa[a]]<<endl;
            debug<<((int)a==rson[fa[a]])<<endl;*/
            if(a==lson[fa[a]]) lson[fa[a]]=b;
            else rson[fa[a]]=b;
            siz[fa[b]]=siz[lson[fa[b]]]+siz[rson[fa[b]]]+num[b];
        }
        else root=b;
    }
}
void del(int x)
{
	x=query(x);
	//debug<<"deleting"<<x<<endl;
	int at=fa[x];
	while(at) siz[at]--,at=fa[at];
	if(num[x]>1) {--num[x];--siz[x];return;}
	int *pos;
	if(fa[x]) pos=(x==lson[fa[x]]?&lson[fa[x]]:&rson[fa[x]]);
	else pos=&root;
	if(lson[x]==0&&rson[x]==0) {*pos=0,num[x]=siz[x]=0;return;}
	if(lson[x]==0||rson[x]==0) {*pos=lson[x]|rson[x],fa[lson[x]|rson[x]]=fa[x],num[x]=siz[x]=0;return;}
	int pro=rson[x],pf;
	while(lson[pro]) pro=lson[pro];//,debug<<"pro="<<pro<<endl;
	pf=fa[pro];
	while(pf!=x) siz[pf]-=num[pro],pf=fa[pf];
	eatnode(x,pro);
	num[x]=siz[x]=0;
}
int sonpro(int x)
{
    x=rson[x];
    while(lson[x]) x=lson[x];
    return x;
}
int sonpre(int x)
{
    x=lson[x];
    while(rson[x]) x=rson[x];
    return x;
}
int kth(int x)
{
	int pos=root;
	while(1)
	{
        /*debug<<"pos="<<pos<<endl;
        debug<<"x="<<x<<endl;
        debug<<"-="<<(siz[lson[pos]]+num[pos])<<endl;*/
        if((siz[lson[pos]]+num[pos])<0) {debug<<"siz<0\n";exit(0);}
		if(x<=siz[lson[pos]]) pos=lson[pos];
		else if(x>siz[lson[pos]]+num[pos]) x-=(siz[lson[pos]]+num[pos]),pos=rson[pos];
		else {splay(pos);return dat[pos];}
	}
}
int getpos(int x)
{
    int pos=query(x);
    int ret=1+siz[lson[pos]];
    while(pos)
    {
        if(pos==rson[fa[pos]]) ret+=siz[lson[fa[pos]]]+num[fa[pos]];
        pos=fa[pos];
    }
    return ret;
}
int globalpro(int x)
{
    if(rson[x]) return dat[sonpro(x)];
    while(x!=lson[fa[x]]) x=fa[x];
    return dat[fa[x]];
}
int globalpre(int x)
{
    if(lson[x]) return dat[sonpre(x)];
    while(x!=rson[fa[x]]) x=fa[x];
    return dat[fa[x]];
}
int getpro(int x)
{
	int q=query(x);
	if(q) return globalpro(q);
	int pos=root;
	while(1)
	{
		if(x<dat[pos])
		{
			if(lson[pos]) pos=lson[pos];
			else return dat[pos];
		}
		else
		{
			if(rson[pos]) pos=rson[pos];
			else
			{
				while(pos!=lson[fa[pos]]) pos=fa[pos];
				return dat[fa[pos]];
			}
		}
	}
}
int getpre(int x)
{
	int q=query(x);
	if(q) return globalpre(q);
	int pos=root;
	while(1)
	{
		if(x<dat[pos])
		{
			if(lson[pos]) pos=lson[pos];
			else
			{
				while(pos!=rson[fa[pos]]) pos=fa[pos];
				return dat[fa[pos]];
			}
		}
		else
		{
			if(rson[pos]) pos=rson[pos];
			else return dat[pos];
		}
	}
}
int debugcnt;
void debugnode()
{
	debug<<"root="<<root<<endl;
	for(int i=debugcnt;i<=cnt;i++)
	{
		if(num[i])
		{
			debug<<"node"<<i<<endl;
			debug<<"    dat="<<dat[i]<<endl;
			debug<<"	fa="<<fa[i]<<endl;
			debug<<"	lson="<<lson[i]<<"rson="<<rson[i]<<endl;
            debug<<"    siz="<<siz[i]<<endl;
            debug<<"	num="<<num[i]<<endl;
		}
	}
}
void checksize()
{
    for(int i=1;i<=cnt;i++) if(num[i]&&siz[i]<0) {debug<<"siz["<<i<<"]<0"<<"\n";debug<<siz[i]<<"    "<<num[i]<<endl;exit(0);}
}
int main()
{
	freopen("dat.txt","r",stdin);
    int n;
    scanf("%d",&n);
    int x,q;
    for(int i=1;i<=n;i++)
    {
    	//debug<<"i="<<i<<"\n";
    	if(!root)
    	{
    		debugcnt=cnt+1;
    		while(q!=1&&i<=n) i++,scanf("%d%d",&q,&x);
    		if(i>n) return 0;
    		root=++cnt;
    		dat[cnt]=x;
    		siz[cnt]=num[cnt]=1;
    	}
    	//debugnode();
    	//checksize();
        scanf("%d%d",&q,&x);
        if(q==1) insert(x);
        else if(q==2) del(x);
        else if(q==3) printf("%d\n",getpos(x));
        else if(q==4) printf("%d\n",kth(x));
        else if(q==5) printf("%d\n",getpre(x));
        else if(q==6) printf("%d\n",getpro(x));
    }
    return 0;
}

