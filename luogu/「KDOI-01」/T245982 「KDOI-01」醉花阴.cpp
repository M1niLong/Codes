#include <bits/stdc++.h>
#define int long long
#define mst(f, i) memset(f, i, sizeof f)
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
int T;
int n, m, k, a[1005][1005];
char c[1005][1005];
int sx, sy, ex, ey, xx[] = {1, -1, 0, 0}, yy[] = {0, 0, 1, -1};
struct node{
    int x, y, typ;// 0:猎人, 1:动物
    // bool operator<(const node b)const{
    //     return typ > b.typ;
    //     return t > b.t;
    // }
};
struct lr{
    int x, y;
}e[1005];
bool vis[1005][1005];
bool bfs(){
    queue<node> q;
    for(int i = 1; i <= k; ++i){
        if(e[i].x == sx && e[i].y == sy || e[i].x == ex && e[i].y == ey) return 0;
        q.push(node{e[i].x, e[i].y, 0});
        a[e[i].x][e[i].y] = 2;
    }
    q.push(node{sx, sy, 1});
    a[sx][sy] = 2;
    while(q.size()){
        node u = q.front();
        q.pop();
        int x = u.x, y = u.y;
        // cout << x << ' ' << y << ' ' << t << ' ' << u.typ << endl;
        for(int i = 0; i < 4; ++i) {
            int nx = x + xx[i], ny = y + yy[i];
            if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
            if(a[nx][ny] == 1 || a[nx][ny] == 2) continue;
            if(nx == ex && ny == ey && u.typ == 1) return 1;
            q.push(node{nx, ny, u.typ});
            a[nx][ny] = 2;
        }
    }
    return 0;
}
signed main(){
    read(T);
    while(T--){
        mst(a, 0), mst(vis, 0), mst(e, 0);
        read(n, m);
        for(int i = 1; i <= n; ++i){
            scanf("%s", c[i]);
            for(int j = 1; j <= m; ++j){
                a[i][j] = c[i][j-1] - '0';
            }
        }
        read(k);
        for(int i = 1, x, y; i <= k; ++i){
            read(x, y);
            e[i] = lr{x, y};
        }
        read(sx, sy, ex, ey);
        if(bfs()) puts("T");
        else puts("F");
        // for(int i = 1; i <= n; ++i){
        //     for(int j = 1; j <= m; ++j){
        //         cout << a[i][j] << ' ';
        //     }
        //     cout << endl;
        // }
    }
    return 0;
}