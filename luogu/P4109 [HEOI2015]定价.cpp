#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, block, num;
int v(int x, int &cnt){
    int len = 0, t = x;
    while(!(x % 10)) x /= 10, t = x, cnt++;
    while(t) len++, t /= 10;
    // cout << x << ' ' << cnt << ' ' << len << endl;
    return (x % 10 == 5) ? 2 * len - 1 : 2 * len;
}
int T;
signed main(){
    scanf("%lld", &T);
    while(T--){
        int l, r, ans = 2e9, k = 0;
        scanf("%lld%lld", &l, &r);
        while(l <= r){
            // cout << l << ' ';
            int cnt = 0;
            int t = v(l, cnt);
            if(t < ans) ans = t, k = l;
            l += pow(10, cnt);
        }
        printf("%lld\n", k);
    }
    return 0;
}