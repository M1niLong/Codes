#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#define endl '\n'
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
    template<typename T> void write(T t, bool f = 0){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10, 1);
        putchar(t % 10 + '0');
        if(!f) puts("");
    }
}
using namespace fastio;
const int N = 5e5 + 5;
int n, q, a[N], l = 1, r, st[N], tp[N], top;
int block, ans[N], cnt[N];
struct query{
    int l, r, id;
    bool operator<(const query b)const{
        return (l / block ^ b.l / block) ? l < b.l : ((l / block) & 1 ? r < b.r : r > b.r);
    }
}Q[N];
void add(int x){
    if(cnt[a[x]] == 0) st[++top] = a[x], tp[a[x]] = top;
    if(cnt[a[x]] == 1) st[tp[a[x]]] = st[top], tp[st[top]] = tp[a[x]], st[top--] = tp[a[x]] = 0;
    cnt[a[x]]++;
}
void del(int x){
    if(cnt[a[x]] == 2) st[++top] = a[x], tp[a[x]] = top;
    if(cnt[a[x]] == 1) st[tp[a[x]]] = st[top], tp[st[top]] = tp[a[x]], st[top--] = tp[a[x]] = 0;
    cnt[a[x]]--;
}
signed main(){
    read(n);
    for(int i = 1; i <= n; ++i) read(a[i]);
    read(q);
    block = sqrt(n);
    for(int i = 1; i <= q; ++i) read(Q[i].l, Q[i].r), Q[i].id = i;
    sort(Q + 1, Q + 1 + q);
    st[++top] = 0;
    for(int i = 1; i <= q; ++i){
        while(l > Q[i].l) add(--l);
        while(r < Q[i].r) add(++r);
        while(l < Q[i].l) del(l++);
        while(r > Q[i].r) del(r--);
        ans[Q[i].id] = st[top];
    }
    for(int i = 1; i <= q; ++i) write(ans[i]);
    return 0;
}
