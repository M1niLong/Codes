#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m, a[N], b[N], block;
int cnt, head[N];
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
struct edge{
    int v, nxt;
}e[N << 1];
void Add(int u, int v){
    e[++cnt] = edge{v, head[u]};
    head[u] = cnt;
}
struct query{
    int l, r, ll, rr, lca, id;
    bool operator<(const query b)const{
        return (ll ^ b.ll) ? l < b.l : (ll & 1 ? r < b.r : r > b.r);
    }
}q[N];
int dep[N], in[N], out[N], fa[N], siz[N], num[N], dfn, top[N], son[N];
void dfs1(int u, int f, int d){
    fa[u] = f, dep[u] = d, in[u] = ++dfn, siz[u] = 1, num[dfn] = u;
    int maxson = -1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == f) continue;
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if(siz[v] > maxson){
            maxson = siz[v];
            son[u] = v;
        }
    }
    out[u] = ++dfn, num[dfn] = u;
}
void dfs2(int u, int topf){
    top[u] = topf; 
    if(son[u]) dfs2(son[u], topf);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v != son[u] && v != fa[u]) dfs2(v, v);
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
bool vis[N];
int res, c[N], ans[N];
void add(int x){
    res += !(c[a[x]]++);
}
void del(int x){
    res -= !(--c[a[x]]);
}
void calc(int x){
    if(vis[x]) del(x);
    else add(x);
    vis[x] ^= 1;
}
signed main(){
    read(n, m);
    for(int i = 1; i <= n; ++i) read(a[i]), b[i] = a[i];
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + len, a[i]) - b;
    for(int i = 1, u, v; i < n; ++i){
        read(u, v);
        Add(u, v), Add(v, u);
    }
    dfs1(1, 0, 0);
    dfs2(1, 1);
    block = sqrt(n);
    for(int i = 1, u, v; i <= m; ++i){
        read(u, v);
        if(in[u] > in[v]) swap(u, v);
        q[i].id = i, q[i].lca = lca(u, v);
        if(q[i].lca == u){
            q[i].l = in[u], q[i].r = in[v];
            q[i].ll = in[u] / block, q[i].rr = in[v] / block;
            q[i].lca = 0;
        }else{
            q[i].l = out[u], q[i].r = in[v];
            q[i].ll = out[u] / block, q[i].rr = in[v] / block;
        }
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i){
        while(l > q[i].l) calc(num[--l]);
        while(l < q[i].l) calc(num[l++]);
        while(r < q[i].r) calc(num[++r]);
        while(r > q[i].r) calc(num[r--]);
        if(q[i].lca) calc(q[i].lca);
        ans[q[i].id] = res;
        if(q[i].lca) calc(q[i].lca);
    }
    for(int i = 1; i <= m; ++i) write(ans[i]), puts("");
    return 0;
}