#include <bits/stdc++.h>
#define int long long
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
const int N = 1e5 + 5;
int n, c[N];
int head[N], ecnt;
struct edge{
    int v, nxt;
}e[N << 1];
void add(int u, int v){
    e[++ecnt] = edge{v, head[u]};
    head[u] = ecnt;
}
int siz[N], son[N];
void dfs1(int u, int fa){
    siz[u] = 1;
    int maxson = -1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxson) son[u] = v, maxson = siz[v];
    }
}
int sum, maxn, Son, cnt[N], ans[N];
void add(int u, int fa, int val){
    cnt[c[u]] += val;
    if(cnt[c[u]] > maxn) maxn = cnt[c[u]], sum = c[u];
    else if(cnt[c[u]] == maxn) sum += c[u];
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v != fa && v != Son) add(v, u, val);
    }
}
void TreeDsu(int u, int fa, int del){
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v != fa && v != son[u]) TreeDsu(v, u, 1);
    }
    if(son[u]) TreeDsu(son[u], u, 0), Son = son[u];
    add(u, fa, 1);
    Son = 0;
    ans[u] = sum;
    if(del) add(u, fa, -1), sum = maxn = 0;
}
signed main(){
    read(n);
    for(int i = 1; i <= n; ++i) read(c[i]);
    for(int i = 1, u, v; i < n; ++i) read(u, v), add(u, v), add(v, u);
    dfs1(1, 0), TreeDsu(1, 0, 1);
    for(int i = 1; i <= n; ++i) write(ans[i]), putchar(' ');
    puts("");
    return 0;
}