#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100005;
namespace fastio{
    inline void read(int &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    // template<typename T, typename ... Args> inline void read(T &t, Args&... args){
    //     read(t);
    //     read(args...);
    // }
    // template<typename T> void write(T t){
    //     if(t < 0) putchar('-'), t = -t;
    //     if(t >= 10) write(t / 10);
    //     putchar(t % 10 + '0');
    // }
};
using namespace fastio;
int n, m, w[N], ww[N], len, rt[N];
int cnt, head[N];
struct edge{
    int v, nxt;
}e[N << 1];
void add(int u, int v){
    e[++cnt] = (edge){v, head[u]};
    head[u] = cnt;
}
int num;
struct CMT{
    int ls, rs, sum;
}a[N << 6];
int New(int x){
    a[++num] = a[x];
    return num;
}
void change(int &x, int pre, int l, int r, int p){
    x = New(pre), a[x].sum++;
    if(l == r) return;
    int mid = l + r >> 1;
    if(p <= mid) change(a[x].ls, a[pre].ls, l, mid, p);
    else change(a[x].rs, a[pre].rs, mid + 1, r, p);
}
int query(int x, int y, int z, int zz, int l, int r, int k){
    int sum = a[a[x].ls].sum + a[a[y].ls].sum - a[a[z].ls].sum - a[a[zz].ls].sum;
    if(l == r) return l;
    int mid = l + r >> 1;
    if(k <= sum) return query(a[x].ls, a[y].ls, a[z].ls, a[zz].ls, l, mid, k);
    else return query(a[x].rs, a[y].rs, a[z].rs, a[zz].rs, mid + 1, r, k - sum);
}
int dfn, dep[N], fa[N], siz[N], son[N], top[N], id[N];
void dfs1(int u, int f, int d){
    dep[u] = d, fa[u] = f, siz[u] = 1;
    int maxson = -1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == f) continue;
        change(rt[v], rt[u], 1, len, w[v]);
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if(siz[v] > maxson) maxson = siz[v], son[u] = v;
    }
}
void dfs2(int u, int topf){
    top[u] = topf, id[u] = ++dfn;
    if(son[u]) dfs2(son[u], topf);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(id[v]) continue;
        dfs2(v, v);
    }
}
int lca(int u, int v){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    return u; 
}
signed main(){
    read(n), read(m);
    for(int i = 1; i <= n; ++i){
        read(w[i]), ww[i] = w[i];
    }
    sort(ww + 1, ww + 1 + n);
    len = unique(ww + 1, ww + 1 + n) - ww - 1;
    for(int i = 1; i <= n; ++i) w[i] = lower_bound(ww + 1, ww + 1 + len, w[i]) - ww;
    for(int i = 1, u, v; i < n; ++i){
        read(u), read(v);
        add(u, v), add(v, u);
    }
    change(rt[1], rt[0], 1, len, w[1]);
    dfs1(1, 0, 0), dfs2(1, 1);
    while(m--){
        int u, v, k, LCA;
        read(u), read(v), read(k);
        LCA = lca(u, v);
        int t = query(rt[u], rt[v], rt[LCA], rt[fa[LCA]], 1, len, k);
        printf("%lld\n", ww[t]);
    }
    return 0;
}