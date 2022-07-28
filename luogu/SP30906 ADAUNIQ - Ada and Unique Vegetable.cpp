#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -1;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t), read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
}
using namespace fastio;
int n, m, a[N], cntq, cntc, block;
struct Query{
    int l, r, t, id;
    bool operator<(const Query b)const{
        if(l / block != b.l / block) return l / block < b.l / block;
        if(r / block != b.r / block) return r / block < b.r / block;
        return t < b.t;
    }
}q[N];
struct Change{
    int x, y;
}c[N];
int ans[N], res, cnt[N];
void add(int x){
    if(cnt[x] == 1) res--;
    if(cnt[x] == 0) res++;
    cnt[x]++;
}
void del(int x){
    if(cnt[x] == 1) res--;
    if(cnt[x] == 2) res++;
    cnt[x]--;
}
void work(int l, int r, int t){
    if(c[t].x >= l && c[t].x <= r){
        del(a[c[t].x]);
        add(c[t].y);
    }
    swap(c[t].y, a[c[t].x]);
}
int main(){
    read(n, m);
    block = pow(n, 2.0 / 3);
    for(int i = 1; i <= n; ++i) read(a[i]);
    for(int i = 1; i <= m; ++i){
        int opt, x, y;
        read(opt, x, y);
        if(opt == 1){
            c[++cntc] = Change{++x, y};
        }else{
            q[++cntq] = Query{++x, ++y, cntc, cntq};
        }
    }
    sort(q + 1, q + 1 + cntq);
    int l = 1, r = 0, t = 0;
    for(int i = 1; i <= cntq; ++i){
        while(l > q[i].l) add(a[--l]);
        while(r < q[i].r) add(a[++r]);
        while(l < q[i].l) del(a[l++]);
        while(r > q[i].r) del(a[r--]);
        while(t > q[i].t) work(l, r, t--);
        while(t < q[i].t) work(l, r, ++t);
        
        ans[q[i].id] = res;
    }
    for(int i = 1; i <= cntq; ++i) write(ans[i]), puts("");
    return 0;
}