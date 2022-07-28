#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int cnt1, head1[N];
namespace fastio{
	template <typename T> inline void read(T &t){
	    t = 0;
	    char c = getchar();
	    int f = 1;
	    while(!isdigit(c)){
	        if (c == '-'){
	            f = -f;
	        }
	        c = getchar();
	    }
	    while(isdigit(c)){
	        t = (t << 3) + (t << 1) + (c ^ '0');
	        c = getchar();
	    }
	    t *= f;
	}
	template <typename T, typename ... Args> inline void read(T &t, Args&... args){
	    read(t);
	    read(args...);
	}
};
using namespace fastio;

struct edge{
    int v, nxt;
}e1[N];
void add1(int u, int v){
    e1[++cnt1] = edge{v, head1[u]};
    head1[u] = cnt1;
}
int cnt, head[N], num;
struct Round_Square_Tree{
    int v, nxt;
}e[N];
void add(int u, int v){
    e[++cnt] = Round_Square_Tree{v, head[u]};
    head[u] = cnt;
}
int dfn[N], low[N], tim, stk[N], tp;
void tarjan(int u){
    dfn[u] = low[u] = ++tim, stk[++tp] = u;
    for(int i = head1[u]; i; i = e1[i].nxt){
        int v = e1[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]){
                num++;
                for(int x = 0; x != v; --tp){
                    x = stk[tp];
                    add(num, x), add(x, num);
                }
                add(num, u), add(u, num);
            }
        }else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
int w[N], W[N];
int top[N], id[N], dep[N], fa[N], son[N], dfc, siz[N];
void dfs1(int u, int f){
    fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
    int maxson = -1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxson) maxson = siz[v], son[u] = v;
    }
}
void dfs2(int x, int topf){
    top[x] = topf, id[x] = ++dfc;
    W[id[x]] = x;
    if(son[x]) dfs2(son[x], topf);
    for(int i = head[x]; i; i = e[i].nxt){
        int v = e[i].v;
        if(!id[v]) dfs2(v, v);
    }
}
struct Tree{
    int l, r, minx;
    #define ls x << 1
    #define rs x << 1 | 1
}a[N << 2];
void update(int x){
    a[x].minx = min(a[ls].minx, a[rs].minx);
}
void build(int x, int l, int r){
    a[x].l = l, a[x].r = r;
    if(l == r){
        a[x].minx = w[W[l]];
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    update(x);
}
void change(int x, int p, int v){
    if(a[x].l == a[x].r){
        a[x].minx = v;
        return;
    }
    int mid = a[x].l + a[x].r >> 1;
    if(p <= mid) change(ls, p, v);
    else change(rs, p, v);
    update(x);
}
int query(int x, int l, int r){
    if(a[x].l >= l && a[x].r <= r) return a[x].minx;
    int mid = a[x].l + a[x].r >> 1, ans = 2e9;
    if(l <= mid) ans = min(ans, query(ls, l, r));
    if(r > mid) ans = min(ans, query(rs, l, r));
    return ans;
}
multiset<int> ms[N];
int n, m, q;
int Tsum(int x, int y){
    int ans = 2e9;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = min(ans, query(1, id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    ans = min(ans, query(1, id[x], id[y]));
    if(x > n) ans = min(ans, w[fa[x]]);
    return ans;
}
signed main(){
    read(n, m, q);
    num = n;
    for(int i = 1; i <= n; ++i) read(w[i]);
    for(int i = 1, u, v; i <= m; ++i){
        read(u, v);
        add1(u, v), add1(v, u);
    }    
    for(int i = 1   ; i <= n; ++i) if(!dfn[i]) tarjan(i);
    dfs1(1, 0);
    dfs2(1, 1);
    for(int i = 2; i <= n; ++i) ms[fa[i] - n].insert(w[i]);
    for(int i = n + 1; i <= num; ++i) w[i] = ms[i - n].empty() ? 2e9 : *ms[i - n].begin();
    build(1, 1, num);
    while(q--){
        char opt[2];
        int x, y;
        scanf("%s", opt);
        read(x, y);
        if(opt[0] == 'A') printf("%d\n", Tsum(x, y));
        else {
            change(1, id[x], y);
            if(x == 1){
                w[x] = y;
                continue;
            }
            int z = fa[x];
            ms[z - n].erase(ms[z - n].find(w[x]));
            ms[z - n].insert(y);
            int minx = *ms[z - n].begin();
            if(minx == w[z]) w[x] = y;
            else {
                change(1, id[z], minx);
                w[z] = minx, w[x] = y;
            }
        }
    }
    return 0;
}