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
const int N = 1e4 + 5, M = 105, K = 1e7 + 5;
int n, m;
int cnt, head[N];
struct edge{
    int v, w, nxt;
}e[N << 1];
void add(int u, int v, int w){
    e[++cnt] = edge{v, w, head[u]};
    head[u] = cnt;
}
int query[M], siz[N], maxn[N], rt, sum;
bool vis[N];
void find(int u, int fa){
    siz[u] = 1, maxn[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v != fa && !vis[v]){
            find(v, u);
            siz[u] += siz[v];
            maxn[u] = max(maxn[u], siz[v]);
        }
    }
    maxn[u] = max(maxn[u], sum - siz[u]);
    if(maxn[u] < maxn[rt]) rt = u;
}
int dis[N], rem[N], cntr;
void getdis(int u, int fa){
    rem[++cntr] = dis[u];
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(v != fa && !vis[v] && dis[u] + w <= 1e7){
            dis[v] = dis[u] + w;
            getdis(v, u);
        }
    }
}
bool judge[K], ans[N];
int tmp[N];
void calc(int u){
    int cntj = 0;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(!vis[v]){
            cntr = 0;
            dis[v] = w;
            getdis(v, u);
            for(int j = cntr; j; --j)
            for(int k = 1; k <= m; ++k){
                if(query[k] < rem[j]) continue;
                ans[k] |= judge[query[k] - rem[j]];
            }
            for(int j = cntr; j; --j){
                judge[rem[j]] = 1, tmp[++cntj] = rem[j];
            }
        }
    }
    for(int i = 1; i <= cntj; ++i) judge[tmp[i]] = 0;
}
void solve(int u){
    judge[0] = vis[u] = 1, calc(u);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(!vis[v]){
            sum = siz[v], rt = 0;
            maxn[rt] = 2e9;
            find(v, 0);
            solve(rt);
        }
    }
}
signed main(){
    read(n, m);
    for(int i = 1, u, v, w; i < n; ++i) read(u, v, w), add(u, v, w), add(v, u, w);
    for(int i = 1; i <= m; ++i) read(query[i]);
    maxn[rt] = sum = n;
    find(1, 0);
    solve(rt);
    for(int i = 1; i <= m; ++i) puts(ans[i] ? "AYE" : "NAY");
    return 0;
}