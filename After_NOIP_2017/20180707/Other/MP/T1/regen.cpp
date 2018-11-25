#include<bits/stdc++.h>
#define debug cerr
using namespace std;

int main(int argc,char** argv) {
    int hsh = std::hash<string>()("KurenaiKisaragi");
    cerr<<"hash = "<<hsh<<endl;
    FILE *in = fopen(argv[1],"r") , *out = fopen(argv[2],"r") , *mer = fopen(argv[3],"w");
    static int n,m;
    fscanf(in,"%d%d",&n,&m) , fprintf(mer,"%d %d\n",n,m);
    while(n--) {
        int x,y;
        fscanf(in,"%d%d",&x,&y) , fprintf(mer,"%d %d\n",x,y);
    }
    while(m--) {
        int x,y,w;
        fscanf(in,"%d%d%d",&x,&y,&w) , fprintf(mer,"%d %d %d\n",x,y,w);
    }
    int ans; fscanf(out,"%d",&ans) , fprintf(mer,"%d\n",ans^hsh);
    return 0;
}

