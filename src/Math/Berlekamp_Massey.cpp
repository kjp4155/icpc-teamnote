#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
#include<tuple>
typedef long long lint;

lint mod = 1000000007;
using namespace std;

lint ipow(lint a, lint b) {
    lint r = 1;
    while (b) {
        if (b & 1)r = r*a%mod;
        b >>= 1, a = a*a%mod;
    }
    return r;
}

vector<lint> berlekamp_massey(vector<lint> x) {
    vector<lint> ls, cur;
    lint lf, ld;
    for (lint i = 0; i<x.size(); i++) {
        lint t = 0;
        for (lint j = 0; j<cur.size(); j++) {
            t = (t + 1ll * x[i - j - 1] * cur[j]) % mod;
        }
        if ((t - x[i]) % mod == 0) continue;
        if (cur.empty()) {
            cur.resize(i + 1);
            lf = i;
            ld = (t - x[i]) % mod;
            continue;
        }
        lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
        vector<lint> c(i - lf - 1);
        c.push_back(k);
        for (auto &j : ls) c.push_back(-j * k % mod);
        if (c.size() < cur.size()) c.resize(cur.size());
        for (lint j = 0; j<cur.size(); j++) {
            c[j] = (c[j] + cur[j]) % mod;
        }
        if (i - lf + (lint)ls.size() >= (lint)cur.size()) {
            tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
        }
        cur = c;
    }
    for (auto &i : cur) i = (i % mod + mod) % mod;
    return cur;
}
lint get_nth(vector<lint> rec, vector<lint> dp, lint n) {
    lint m = rec.size();
    vector<lint> s(m), t(m);
    s[0] = 1;
    if (m != 1) t[1] = 1;
    else t[0] = rec[0];
    auto mul = [&rec](vector<lint> v, vector<lint> w) {
        lint m = v.size();
        vector<lint> t(2 * m);
        for (lint j = 0; j<m; j++) {
            for (lint k = 0; k<m; k++) {
                t[j + k] += 1ll * v[j] * w[k] % mod;
                if (t[j + k] >= mod) t[j + k] -= mod;
            }
        }
        for (lint j = 2 * m - 1; j >= m; j--) {
            for (lint k = 1; k <= m; k++) {
                t[j - k] += 1ll * t[j] * rec[k - 1] % mod;
                if (t[j - k] >= mod) t[j - k] -= mod;
            }
        }
        t.resize(m);
        return t;
    };
    while (n) {
        if (n & 1) s = mul(s, t);
        t = mul(t, t);
        n >>= 1;
    }
    lint ret = 0;
    for (lint i = 0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
    return ret % mod;
}
lint guess_nth_term(vector<lint> x, lint n) {
    if (n < x.size()) return x[n];
    vector<lint> v = berlekamp_massey(x);
    if (v.empty()) return 0;
    return get_nth(v, x, n);
}