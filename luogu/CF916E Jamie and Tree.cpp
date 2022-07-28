#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
int n, root, w[N];
int head[N], cnt;
struct edge{
    int v, nxt;
}e[N];
void add(int u, int v){
    e[++cnt] = edge{v, head[u]};
    head[u] = cnt;
}
int dfn, id[N], dep[N], fa[N], siz[N], f[N][20], W[N];
void dfs(int u, int fat){
    id[u] = ++dfn, dep[u] = dep[fat] + 1, siz[u] = 1, f[u][0] = fat;
    W[id[u]] = w[u];
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fat) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
}
struct Tree{
    int l, r, sum, add;
    #define ls x << 1
    #define rs x << 1 | 1
}a[N << 2];
void update(int x){
    a[x].sum = a[ls].sum + a[rs].sum;
}
void pushdown(int x){
    a[ls].sum += (a[ls].r - a[ls].l + 1) * a[x].add, a[rs].sum += (a[rs].r - a[rs].l + 1) * a[x].add;
    a[ls].add += a[x].add, a[rs].add += a[x].add;
    a[x].add = 0;
}
void build(int x, int l, int r){
    a[x].l = l, a[x].r = r;
    if(l == r){
        a[x].sum = W[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    update(x);
}
void Add(int x, int l, int r, int v){
    if(a[x].l >= l && a[x].r <= r){
        a[x].sum += (a[x].r - a[x].l + 1) * v, a[x].add += v;
        return;
    }
    pushdown(x);
    int mid = a[x].l + a[x].r >> 1;
    if(l <= mid) Add(ls, l, r, v);
    if(r > mid) Add(rs, l, r, v);
    update(x);
}
int query(int x, int l, int r){
    if(a[x].l >= l && a[x].r <= r) return a[x].sum;
    pushdown(x);
    int mid = a[x].l + a[x].r >> 1, sum = 0;
    if(l <= mid) sum += query(ls, l, r);
    if(r > mid) sum += query(rs, l, r);
    return sum;
}
void st_create(){
    for(int i = 1; i <= 17; ++i){
        for(int j = 1; j <= n; ++j){
            f[j][i] = f[f[j][i-1]][i-1];
        }
    }
}
int jump(int u, int h){
    int p = 0;
    while(h){
        if(h & 1) u = f[u][p];
        h >>= 1, p++;
    }
    return u;
}
int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    x = jump(x, dep[x] - dep[y]);
    // puts("ccf");
    if(x == y) return x;
    for(int i = 17; i >= 0; --i) {
        if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
int getlca(int x, int y){
    int a = lca(x, y), b = lca(x, root), c = lca(y, root);
    if(dep[b] > dep[a]) a = b;
    if(dep[c] > dep[a]) a = c;
    return a;
}
void Tadd(int L, int R, int v){
    int x = getlca(L, R);
    // puts("fucj");
    int l = id[x], r = id[x] + siz[x] - 1;
    if(root == x) Add(1, 1, n, v);
    else if(l > id[root] || r < id[root]) Add(1, l, r, v);
    else {
        int son = jump(root, dep[root] - dep[x] - 1);
        Add(1, 1, n, v), Add(1, id[son], id[son] + siz[son] - 1, -v);
    }
}
int Tquery(int x){
    int l = id[x], r = id[x] + siz[x] - 1;
    if(root == x) return query(1, 1, n);
    else if(l > id[root] || r < id[root]) return query(1, l, r);
    else {
        int son = jump(root, dep[root] - dep[x] - 1);
        return query(1, 1, n) - query(1, id[son], id[son] + siz[son] - 1);
    }
}
int q;
signed main(){
    root = 1;
    scanf("%lld%lld", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%lld", &w[i]);
    for(int i = 1, u, v; i < n; ++i){
        scanf("%lld%lld", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    st_create();
    build(1, 1, n);
    while(q--){
        int opt, u, v, x;
        scanf("%lld", &opt);
        if(opt == 1) scanf("%lld", &root);
        if(opt == 2){
            scanf("%lld%lld%lld", &u, &v, &x);
            Tadd(u, v, x);
        }
        if(opt == 3){
            scanf("%lld", &u);
            printf("%lld\n", Tquery(u));
        }
    }
    return 0;
}