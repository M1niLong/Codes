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
int z, k;
signed main(){
    cin >> z >> k;
    if(k <= z) cout << z * 2 << endl;
    else{
        int t = (int)ceil((double)k / (double)z);
        cout << z * (t + 1) << endl;
    }
    return 0;
}