#include <bits/stdc++.h>
#define ls i << 1
#define rs i << 1 | 1
using namespace std;
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
const int N = (int)(1e6+1);
int n, m, root, mod;
int cnt, head[N];
struct edge{
	int v, nxt;
}e[N * 2];
void add(int u, int v){
	e[++cnt] = edge{v, head[u]};
	head[u] = cnt;
}
struct Tree{
	int sum, l, r;
}tree[N * 4];
int dfn;
int siz[N], son[N], w[N], a[N], f[N], dep[N], id[N], top[N];
void dfs1(int u, int fa, int d){
	dep[u] = d;
	f[u] = fa;
	siz[u] = 1;
	int maxson = -1;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(v == fa) continue;
		dfs1(v, u, d + 1);
		siz[u] += siz[v];
		if(siz[v] > maxson) son[u] = v, maxson = siz[v];
	}
}
void dfs2(int u, int topf){
	id[u] = ++dfn;
	w[dfn] = a[u];
	top[u] = topf;
	if(!son[u]) return;
	dfs2(son[u], topf);
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(id[v]) continue;
		dfs2(v, v);
	}
}
void update(int i){
	tree[i].sum = tree[ls].sum + tree[rs].sum;
}
void build(int i, int l, int r){
	tree[i].l = l, tree[i].r = r;
	if(l == r){
		tree[i].sum = w[l];
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(i);
}
void add_segment(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){
		tree[i].sum += (tree[i].r - tree[i].l + 1) * k;
		return;
	}
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) add_segment(ls, l, r, k);
	if(r > mid) add_segment(rs, l, r, k);
	update(i);
}
int query(int i, int l, int r){
	if(tree[i].l >= l && tree[i].r <= r){
		return tree[i].sum;
	}
	int mid = tree[i].l + tree[i].r >> 1;
	int sum = 0;
	if(l <= mid) sum += query(ls, l, r);
	if(r > mid) sum += query(rs, l, r);
	return sum;
}
int Tsum(int l, int r){
	int res = 0;
	while(top[l] != top[r]){
		if(dep[top[l]] < dep[top[r]]) swap(l, r);
		res += query(1, id[top[l]], id[l]);
		l = f[top[l]];
	}
	if(dep[l] > dep[r]) swap(l, r);
	res += query(1, id[l], id[r]);
	return res;
}
signed main(){
	read(n, m);
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1; i < n; ++i){
		int x, y;
		read(x, y);
		add(x, y), add(y, x);
	}
	dfs1(1, -1, 1);
	dfs2(1, 1);
	build(1, 1, n);
	while(m--){
        int opt, x, y;
        read(opt);
        if(opt == 1){
            read(x, y);
            write(Tsum(x, y));
            puts("");
        }
        if(opt == 2){
            read(x);
            write(query(1, id[x], id[x] + siz[x] - 1));
            puts("");
        }
        if(opt == 3){
            read(x, y);
            add_segment(1, id[x], id[x], y);
        }
    }
	return 0;
}
