#include <bits/stdc++.h>
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
};
using namespace fastio;
const int N = 100005;
int q, pos, cnt, rt[N];
struct Tree{
    int ls, rs, siz;
    char c;
}a[N << 6];
int New(int x){
    a[++cnt] = a[x];
    return cnt;
}
void update(int &x, int pre, int l, int r, char w){
    x = New(pre);
    if(l == r){
        a[x].c = w;
        a[x].siz = 1;
        return;
    }
    int mid = l + r >> 1;
    if(a[a[x].ls].siz == mid - l + 1) update(a[x].rs, a[pre].rs, mid + 1, r, w);
    else update(a[x].ls, a[pre].ls, l, mid, w);
    a[x].siz = a[a[x].ls].siz + a[a[x].rs].siz;
}
char query(int x, int l, int r, int p){
    if(l >= r) return a[x].c;
    int mid = l + r >> 1;
    if(p <= a[a[x].ls].siz) return query(a[x].ls, l, mid, p);
    else return query(a[x].rs, mid + 1, r, p - a[a[x].ls].siz);
}
int main(){
    read(q);
    int t = 0;
    for(int i = 1; i <= q; ++i){
        char ch[2], x[2];
        scanf("%s", ch);
        if(ch[0] == 'T'){
            t++;
            scanf("%s", x);
            update(rt[t], rt[t-1], 1, q, x[0]);
        }
        if(ch[0] == 'U'){
            int k;
            read(k);
            t++;
            rt[t] = rt[t - k - 1];
        }
        if(ch[0] == 'Q'){
            int k;
            read(k);
            putchar(query(rt[t], 1, q, k));
            puts("");
        }
    }
    return 0;
}