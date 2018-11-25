#include<cstdio>
#include<set>

std::set<int> es;

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,t;i<=3;i++) scanf("%d",&t) , es.insert(t);
    for(int i=0,j=1,k=2;i<n;i++,j=(j+1)%n,k=(k+1)%n) { // i is the first edge .
        if( es.find(i) != es.end() && es.find(j) != es.end() && es.find(k) != es.end() )
            return puts("TAK"),0;
    }
    puts((n&1)?"NIE":"TAK");
    return 0;
}
