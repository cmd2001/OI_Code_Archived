#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=100100;
int lson[maxn],rson[maxn],fa[maxn],dat[maxn],siz[maxn],num[maxn];
int root,cnt;
void zig(int x)//x is the fa;
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
void insert(int x)// lson:<=, rson:>.
{
    register int pos=root;
    while(1)
    {
        siz[pos]++;
        if(x==dat[pos])
        {
            num[pos]++;
            break;
        }
        if(x<dat[pos])
        {
            if(lson[pos]) pos=lson[pos];
            else
            {
                lson[pos]=++cnt;
                dat[cnt]=x;
                fa[cnt]=pos;
                siz[cnt]=num[cnt]=1;
                break;
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
                break;
            }
        }
    }
}
void splay(int x);
int query(int x)//find a node whose dat == x, return a number of the pos, 0 means not found.
{
    register int pos=root;
    while(pos&&x!=dat[pos]) pos=(x<dat[pos]?lson[pos]:rson[pos]);
    splay(pos);
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
	if(rson[b]) fa[rson[b]]=fa[b];
	if(lson[fa[b]]==b) lson[fa[b]]=rson[b];
	else rson[fa[b]]=rson[b];
	if(lson[a]) fa[lson[a]]=b;
	if(rson[a]) fa[rson[a]]=b;
	siz[fa[b]]-=num[b];
	lson[b]=lson[a],rson[b]=rson[a];
	fa[b]=fa[a];
	if(a!=root)
	{
		if(lson[fa[a]]==a) lson[fa[a]]=b;
		else rson[fa[a]]=b;
	}
	else root=b;
	siz[b]=siz[lson[b]]+siz[rson[b]]+num[b];
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
void del(int x)
{
    int pos=root;
    while(pos&&x!=dat[pos]) {siz[pos]--;pos=(x<dat[pos]?lson[pos]:rson[pos]);}
    if(num[pos]>1) {siz[pos]--,num[pos]--;return;}
    num[pos]=0;
    x=pos;
    //debug<<"deleting"<<x<<endl;
    int *to;
    if(fa[x]) to=(lson[fa[x]]==x?&lson[fa[x]]:&rson[fa[x]]);
    else to=&root;
    siz[pos]--;
    if((!lson[x])&&(!rson[x])) {*to=0;return;}
    if((!lson[x])||(!rson[x])) {*to=lson[x]|rson[x],fa[lson[x]|rson[x]]=fa[x];return;}
    else
    {
        int pro=sonpro(x);
		siz[fa[pro]]-=siz[pro];
        eatnode(x,pro);
        if(lson[fa[pro]]==pro) lson[fa[pro]]=0;
        else rson[fa[pro]]=0;
    }
}
int kth(int x)
{
	int pos=root;
	while(1)
	{
		if(x<=siz[lson[pos]]) pos=lson[pos];
		else if(x>siz[lson[pos]]+num[pos]) x-=(siz[lson[pos]]+num[pos]),pos=rson[pos];
		else return dat[pos];
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
			debug<<"	node"<<i<<endl;
			debug<<"	fa="<<fa[i]<<endl;
			debug<<"	"<<lson[i]<<rson[i]<<endl;
		}
	}
}
int main()
{
	return 0;
	//freopen("dat.txt","r",stdin);
	//freopen("debug.txt","w",stdout);
    int n;
    scanf("%d",&n);
    int x,q;
    for(int i=1;i<=n;i++)
    {
    	debug<<"i="<<i<<endl;
    	if(!root)
    	{
    		debugcnt=cnt+1;
    		while(q!=1) i++,scanf("%d%d",&q,&x),printf("%d\n %d\n",q,x);
    		root=++cnt;
    		dat[cnt]=x;
    		siz[cnt]=num[cnt]=1;
    	}
    	//debugnode();
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


