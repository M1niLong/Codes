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
const int N = 4e5 + 5, K = 1e6 + 5;
int n, m;
int cnt, head[N];
struct edge{
    int v, w, nxt;
}e[N << 1];
void add(int u, int v, int w){
    e[++cnt] = edge{v, w, head[u]};
    head[u] = cnt;
}
int k, siz[N], maxn[N], rt, sum;
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
int dis[N], rem[N], cntr, dep[N];
void getdis(int u, int fa, int ds, int d){
    if(ds > k) return;
    rem[++cntr] = ds, dep[cntr] = d;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(v != fa && !vis[v]){
            getdis(v, u, ds + w, d + 1);
        }
    }
}
int tmp[N], num = 2e9, ct[K];
void calc(int u){
    cntr = 0;
    ct[0] = 0;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(!vis[v]){
            int p = cntr;
            getdis(v, u, w, 1);
            for(int j = p + 1; j <= cntr; ++j) num = min(num, ct[k - rem[j]] + dep[j]);
            for(int j = p + 1; j <= cntr; ++j) ct[rem[j]] = min(ct[rem[j]], dep[j]);
        }
    }
    // for(int i = 1; i <= n; ++i) cout << dep[i] << ' ';
    // cout << endl;
    for(int i = 1; i <= cntr; ++i) ct[rem[i]] = 2e9;
}
void solve(int u){
    vis[u] = 1, calc(u);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(!vis[v]){
            sum = siz[v], rt = 0;
            find(v, u);
            solve(rt);
        }
    }
}
signed main(){
    read(n, k);
    for(int i = 1, u, v, w; i < n; ++i) read(u, v, w), add(++u, ++v, w), add(v, u, w);
    maxn[rt] = (sum = n) + 1;
    memset(ct, 0x3f, sizeof ct);
    find(1, 0);
    solve(rt);
    write(num >= n ? -1 : num);
    puts("");
    return 0;
}