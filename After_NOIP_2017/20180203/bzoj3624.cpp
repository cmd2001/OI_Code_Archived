#include<bits/stdc++.h>
#define I int
#define V void
#define R(x) scanf("%d",x)
#define _ 100100
I f[_],x[_],y[_],t[_],s[_],v[_],n,m,k;I F(I x){return f[x]==x?x:f[x]=F(f[x]);}V M(I x,I y){f[F(x)]=F(y);}I C(I x,I y){return t[x]>t[y];}I J(){I c=0;for(I i=1;i<=n;i++)f[i]=i;for(I i=1;i<=m;i++)if(F(x[s[i]])!=F(y[s[i]])) c+=v[s[i]]=!t[s[i]],M(x[s[i]],y[s[i]]);return c<=k;}V G(){I c=0,C=0;for(I i=1;i<=n;i++)f[i]=i;for(I i=1;i<=m;i++)if(v[i])M(x[i],y[i]),++c;for(I i=m;i&&c<k;i--)if(!t[s[i]]&&F(x[s[i]])!=F(y[s[i]]))c+=v[s[i]]=1,M(x[s[i]],y[s[i]]);for(I i=m;i;i--)if(t[s[i]]&&F(x[s[i]])!=F(y[s[i]]))M(x[s[i]],y[s[i]]),C+=v[s[i]]=1;if(c!=k||c+C!=n-1)puts("no solution");else for(I i=m;i;i--) if(v[i])printf("%d %d %d\n",x[i],y[i],t[i]);}I main(){R(&n),R(&m),R(&k);for(I i=1;i<=m;i++)R(x+i),R(y+i),R(t+i),s[i]=i;std::sort(s+1,s+1+m,C);if(!J()) return puts("no solution"),0;G();return 0;}
