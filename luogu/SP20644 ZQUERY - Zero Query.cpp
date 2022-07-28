#include <bits/stdc++.h>
#define int long long
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
const int N = 2e5 + 5;
int n, m, num, pos[N], block, R[N], L[N], a[N], ans[N], sum[N], s[N], t[N], t2[N];
struct query{
    int l, r, id;
    bool operator<(const query b)const{
        return (pos[l] == pos[b.l]) ? r < b.r : pos[l] < pos[b.l];
    }
}q[N];
void work(){
    int last = 0, l = 1, r = 0, res1 = 0;
    for(int i = 1; i <= m; ++i){
        int ql = q[i].l, qr = q[i].r;
        if(pos[ql] == pos[qr]){
            res1 = 0;
            for(int j = ql; j <= qr; ++j) s[sum[j]] = 0;
            for(int j = ql; j <= qr; ++j){
                if(!s[sum[j]]) s[sum[j]] = j;
                res1 = max(res1, j - s[sum[j]]);
            }
            for(int j = ql; j <= qr; ++j) s[sum[j]] = 0;
            ans[q[i].id] = res1;
            continue;
        }
        int x = pos[ql];
        if(last != x){
            res1 = 0;
            for(int j = l; j <= r; ++j) s[sum[j]] = t[sum[j]] = t2[sum[j]] = 0;
            l = R[x], r = l - 1;
            last = x;
        }
        while(r < qr){
            r++;
            if(!s[sum[r]]) s[sum[r]] = r;
            t[sum[r]] = r;
            res1 = max(res1, r - s[sum[r]]); 
        }
        int p = l, res2 = 0;
        while(p > ql){
            p--;
            if(!t2[sum[p]]) t2[sum[p]] = p;
            res2 = max(res2, max(t2[sum[p]], t[sum[p]]) - p);
        }
        while(p < l){
            t2[sum[p]] = 0;
            p++;
        }
        ans[q[i].id] = max(res1, res2);
    }
}

signed main(){
    read(n, m);
    n++;
    block = sqrt(n), num = (n - 1) / block + 1;
    for(int i = 2; i <= n; ++i) read(a[i]), sum[i] = sum[i-1] + a[i];
    for(int i = 1; i <= m; ++i) read(q[i].l, q[i].r), q[i].id = i, q[i].r++;
    for(int i = 1; i <= num; ++i){
        L[i] = (i - 1) * block + 1, R[i] = min(i * block, n);
        for(int j = L[i]; j <= R[i]; ++j) pos[j] = i;
    }
    sort(q + 1, q + 1 + m);
    work();
    for(int i = 1; i <= m; ++i) write(ans[i]), puts("");
    return 0;
}