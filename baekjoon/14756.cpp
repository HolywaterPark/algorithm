#include<bits/stdc++.h>

using namespace std;

typedef complex<double> cdbl;

using ll = long long;

using cdbl = complex<double>;
 
const double PI = acos(-1);

inline unsigned bitreverse(const unsigned n, const unsigned k) {
    unsigned r, i;
    for (r = 0, i = 0; i < k; ++i)
        r |= ((n >> i) & 1) << (k - i - 1);
    return r;
}

void fft(vector<cdbl> &a, bool is_reverse=false) {
    const unsigned n = a.size(), k = __builtin_ctz(n);
    unsigned s, i, j;
    for (i = 0; i < n; i++) {
        j = bitreverse(i, k);
        if (i < j)
            swap(a[i], a[j]);
    }
    for (s = 2; s <= n; s *= 2) {
        double t = 2*PI/s * (is_reverse? -1 : 1);
        cdbl ws(cos(t), sin(t));
        for (i = 0; i < n; i += s) {
            cdbl w(1);
            for (j = 0; j < s/2; j++) {
                cdbl tmp = a[i + j + s/2] * w;
                a[i + j + s/2] = a[i + j] - tmp;
                a[i + j] += tmp;
                w *= ws;
            }
        }
    }
    if (is_reverse)
        for (i = 0; i < n; i++)
            a[i] /= n;
}

void convolution(vector<cdbl> &a, vector<cdbl> &b) {
    const unsigned n = a.size();
    unsigned np = n, i;
 
    if (n & (n-1)) {
        for (np = 1; np < 2*n; np *= 2);
        a.resize(np);
        b.resize(np);
        for (i = 0; i < n; i++)
            b[np-n+i] = b[i];
    }
 
    fft(a);
    fft(b);
    for (i = 0; i < np; i++)
        a[i] *= b[i];
    fft(a, true);
 
    if (n & (n-1)) {
        a.resize(n);
        b.resize(n);
    }
}

long long n,m,l,w;
long long ans[111][10001];

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int i,j;

    cin >> n >> l >> m >> w;

    vector<cdbl> a[101];
    vector<cdbl> b[101];

    for(i=1; i<=m; i++)
    {
        a[i].resize(n);
        for(j=0; j<n; j++){
            cin >> a[i][j];
        }
    }
    for(i=1; i<=m; i++){
        b[i].resize(n);
        for(j=1; j<=l; j++){
            cin >> b[i][l-j];
        }
    }
    for(i=1; i<=m; i++){
        convolution(a[i],b[i]);
        for(j=l-1; j<n; j++){
            ans[i][j-l+1]=(long long)a[i][j].real();
        }
    }
    int cnt=0;
    for(i=0; i<=n-l; i++){
        long long sum=0;
        for(j=1; j<=m; j++){
            sum+=ans[j][i];
        }
        if(sum>w) cnt++;
    }
    cout << cnt;
    return 0;
}