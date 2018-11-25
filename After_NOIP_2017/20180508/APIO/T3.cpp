#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2;

int arr[maxn],in[maxn],srt[maxn],last,mx,smx,flag,n;

inline bool empty() {
    for(int i=1;i<=mx;i++) if(arr[i]) return 0;
    return 1;
}

int main() {
    scanf("%d",&n);
    if( n == 1 ) return puts("NO"),0;
    for(int i=1;i<=n;i++) scanf("%d",in+i) , srt[i] = in[i];
    std::sort(srt+1,srt+1+n) , mx = srt[n];
    for(int i=n;i&&srt[i]==srt[n];i--) ++smx;
    if( smx == 1 ) return puts("NO"),0;
    if( smx % 10 == 1 ) flag = 1;
    for(int i=1;i<=n;i++) ++arr[srt[i]];
    arr[mx] += flag;
    for(int i=mx;i;i--) arr[i-1] += arr[i] / 10 , arr[i] %= 10; 
    if( *arr && !empty() ) return puts("NO"),0;
    puts("YES");
    for(int i=n;i&&!last;i--) if( in[i] == mx ) last = i;
    if( !*arr) {
        --arr[mx];
        for(int i=mx;i;i--) {
            arr[i] = -arr[i];
            if( arr[i] < 0 ) arr[i] += 10 , arr[i-1] ++;
        }
    } else arr[mx] = 1;
    for(int i=1;i<=n;i++) {
        printf("0.");
        if( in[i] != mx ) {
            for(int j=1;j<in[i];j++) putchar('0');
            puts("1");
        } else {
            if( flag ) {
                for(int j=1;j<in[i];j++) putchar('0');
                puts("2") , flag = 0;
            } else if( i == last ) {
                for(int j=1;j<mx;j++) putchar('0'+arr[j]);
                putchar('0'+arr[mx]);
                putchar('\n');
            } else {
                for(int j=1;j<in[i];j++) putchar('0');
                puts("1");
            }
        }
    }
    return 0;
}
