#include <bits/stdc++.h>
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
const int N = 1e3 + 5;
int T, n;
set<int> t[N], s;

signed main(){
    read(T);
    while(T--){
        int k;
        read(n);
        for(int i = 1; i <= n; ++i){
            read(k);
            t[i].clear();
            for(int j = 1, p; j <= k; ++j){
                read(p);
                t[i].insert((int)log(p));
            }
        }
        for(int i = 2; i <= n; ++i){
            s.clear();
            for(set<int>::iterator j = t[i-1].begin(); j != t[i-1].end(); ++j){
                for(set<int>::iterator p = t[i].begin(); p != t[i].end(); ++p){
                    s.insert(*j + *p);
                }  
            }
            t[i].clear();
            for(set<int>::iterator j = s.begin(); j != s.end(); ++j) t[i].insert(*j);
        }
        write(t[n].size());
        puts("");
    }
    return 0;
}