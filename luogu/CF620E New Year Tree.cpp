#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int n, m;
int head[N], cnt;
struct edge{
    int v, nxt;
}e[N << 1];
void add(int u, int v){
    e[++cnt] = edge{v, head[u]};
    head[u] = cnt;
}
int w[N], id[N], top[N], son[N], dep[N], fa[N], siz[N], W[N], dfn;
void dfs1(int u, int f, int d){
    dep[u] = d, fa[u] = f, siz[u] = 1;
    int maxson = -1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == f) continue;
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if(siz[v] > maxson) maxson = siz[v], son[u] = v;
    }
}
void dfs2(int u, int topf){
    top[u] = topf, id[u] = ++dfn, W[id[u]] = w[u];
    if(son[u]) dfs2(son[u], topf);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(id[v]) continue;
        dfs2(v, v);
    }
}
struct Tree{
    int l, r, cz;
    bool sum[61];
    #define ls x << 1
    #define rs x << 1 | 1
}a[N << 2];
void update(int x){
    for(int i = 1; i <= 60; ++i) 
        a[x].sum[i] = a[ls].sum[i] | a[rs].sum[i];
}
void pushdown(int x){
    if(a[x].cz){
        for(int i = 1; i <= 60; ++i) a[ls].sum[i] = a[rs].sum[i] = 0;
        a[ls].sum[a[x].cz] = 1, a[ls].cz = a[x].cz;
        a[rs].sum[a[x].cz] = 1, a[rs].cz = a[x].cz;
        a[x].cz = 0;
    }
}
void build(int x, int l, int r){
    a[x].l = l, a[x].r = r;
    if(l == r){
        a[x].sum[W[l]] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    update(x);
}
void change(int x, int l, int r, int val){
    if(a[x].l >= l && a[x].r <= r){
        for(int i = 1; i <= 60; ++i) a[x].sum[i] = 0;
        a[x].sum[val] = 1, a[x].cz = val;
        return;
    }
    pushdown(x);
    int mid = a[x].l + a[x].r >> 1;
    if(l <= mid) change(ls, l, r, val);
    if(r > mid) change(rs, l, r, val);
    update(x);
}
bool vis[61];
int query(int x, int l, int r){
    int res = 0;
    if(a[x].l >= l && a[x].r <= r){
        for(int i = 1; i <= 60; ++i){
            if(a[x].sum[i] && !vis[i]) res += a[x].sum[i], vis[i] = 1;
        }
        return res;
    }
    pushdown(x);
    int mid = a[x].l + a[x].r >> 1;
    if(l <= mid) res += query(ls, l, r);
    if(r > mid) res += query(rs, l, r);
    return res;
}
signed main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    for(int i = 1, u, v; i < n; ++i){
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs1(1, 0, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while(m--){
        int opt, u, c;
        scanf("%d%d", &opt, &u);
        if(opt == 1){
            scanf("%d", &c);
            change(1, id[u], id[u] + siz[u] - 1, c);
        }else{
            printf("%d\n", query(1, id[u], id[u] + siz[u] - 1));
            memset(vis, 0, sizeof vis);
        }
    }
    return 0;
}