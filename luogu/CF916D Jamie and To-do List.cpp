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
const int N = 2e5 + 5, L = 20;
int q;
// class Trie{
//     private:
//         struct Tree{
//             int nxt[27], tag = 0;
//         }a[N * L];
//         int cnt = 0, num = 0;
//     public:
//         void Insert(char *ch){
//             int len = strlen(ch), x = 0;
//             for(int i = 0; i < len; ++i){
//                 int v = ch[i] - 'a';
//                 if(!a[x].nxt[v]) a[x].nxt[v] = ++cnt;
//                 x = a[x].nxt[v];
//             }
//             a[x].tag = ++num;
//         }
//         int query(char *ch){
//             int len = strlen(ch), x = 0;
//             for(int i = 0; i < len; ++i){
//                 int v = ch[i] - 'a';
//                 if(!a[x].nxt[v]) return 0;
//                 x = a[x].nxt[v];
//             }
//             return a[x].tag;
//         }
//         int get(char *ch){
//             int p = query(ch);
//             if(!p) Insert(ch), p = num;
//             return p;
//         }
// }trie;
int ct;
map<string, int> mp;
int get(char *ch){
    string t(ch);
    if(!mp.count(t)) mp[t] = ++ct;
    return mp[t];
}
int cnt;
struct Tree{
    int ls, rs, sum;
}a[N<<6];
int New(int x){
    a[++cnt] = a[x];
    return cnt;
}
int rt1[N], rt2[N];//rt1:权值;rt2:数组
void update(int &x, int pre, int l, int r, int p, int w){
    x = New(pre);
    a[x].sum += w;
    if(l == r) return;
    int mid = l + r >> 1;
    if(p <= mid) update(a[x].ls, a[pre].ls, l, mid, p, w);
    else update(a[x].rs, a[pre].rs, mid + 1, r, p, w);
}
int query(int x, int l, int r, int ql, int qr){
    if(l >= ql && qr >= r) return a[x].sum;
    int mid = l + r >> 1, sum = 0;
    if(ql <= mid) sum += query(a[x].ls, l, mid, ql, qr);
    if(qr > mid) sum += query(a[x].rs, mid + 1, r, ql, qr);
    return sum;
}

signed main(){
    read(q);
    for(int i = 1; i <= q; ++i){
        char opt[10], ch[20];
        int k;
        scanf("%s", opt);
        rt1[i] = rt1[i-1], rt2[i] = rt2[i-1];
        if(opt[0] == 's'){
            scanf("%s", ch), read(k);
            int id = get(ch), p = query(rt2[i], 1, 1e9, id, id);
            if(p) update(rt1[i], rt1[i], 1, 1e9, p, -1);
            update(rt1[i], rt1[i], 1, 1e9, k, 1);
            update(rt2[i], rt2[i], 1, 1e9, id, k - p);
        }
        if(opt[0] == 'r'){
            scanf("%s", ch);
            int id = get(ch), p = query(rt2[i], 1, 1e9, id, id);
            if(p) update(rt1[i], rt1[i], 1, 1e9, p, -1);
            update(rt2[i], rt2[i], 1, 1e9, id, -p);
        }
        if(opt[0] == 'q'){
            scanf("%s", ch);
            int id = get(ch), p = query(rt2[i], 1, 1e9, id, id);
            if(!p) puts("-1");
            else if(p == 1) puts("0");
            else printf("%lld\n", query(rt1[i], 1, 1e9, 1, p - 1));
            fflush(stdout);
        }
        if(opt[0] == 'u'){
            read(k);
            rt1[i] = rt1[i - k - 1];
            rt2[i] = rt2[i - k - 1];
        }
    }
    return 0;
}