typedef long long ll;
using namespace std;

ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

namespace miller_rabin {
    ll mul(ll x, ll y, ll mod) { return (__int128)x * y % mod; }
    //ll mul(ll x, ll y, ll mod) { return x * y % mod; }
    ll ipow(ll x, ll y, ll p) {
        ll ret = 1, piv = x % p;
        while (y) {
            if (y & 1) ret = mul(ret, piv, p);
            piv = mul(piv, piv, p);
            y >>= 1;
        }
        return ret;
    }
    bool miller_rabin(ll x, ll a) {
        if (x % a == 0) return 0;
        ll d = x - 1;
        while (1) {
            ll tmp = ipow(a, d, x);
            if (d & 1) return (tmp != 1 && tmp != x - 1);
            else if (tmp == x - 1) return 0;
            d >>= 1;
        }
    }
    bool isprime(ll x) {
        for (auto &i : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
            if (x == i) return 1;
            if (x > 40 && miller_rabin(x, i)) return 0;
        }
        if (x <= 40) return 0;
        return 1;
    }
}
namespace pollard_rho {
    ll f(ll x, ll n, ll c) {
        return (c + miller_rabin::mul(x, x, n)) % n;
    }
    void rec(ll n, vector<ll> &v) {
        if (n == 1) return;
        if (n % 2 == 0) {
            v.push_back(2);
            rec(n / 2, v);
            return;
        }
        if (miller_rabin::isprime(n)) {
            v.push_back(n);
            return;
        }
        ll a, b, c;
        while (1) {
            a = rand() % (n - 2) + 2;
            b = a;
            c = rand() % 20 + 1;
            do {
                a = f(a, n, c);
                b = f(f(b, n, c), n, c);
            } while (gcd(abs(a - b), n) == 1);
            if (a != b) break;
        }
        ll x = gcd(abs(a - b), n);
        rec(x, v);
        rec(n / x, v);
    }
    vector<ll> factorize(ll n) {
        vector<ll> ret;
        rec(n, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }
};

int main() {
    vector<ll> res;
    ll num;
    scanf("%lld", &num);
    res = pollard_rho::factorize(num);
    for (int i = 0; i < res.size(); ++i)
        printf("%lld\n", res[i]);
}

/////////////
// Shanks-Tonelli, Square Root Modulo P
/////////////
long long get_sqrt(long long a, long long Mod) {
    long long tp = Mod - 1, S = 0;
    if (Mod == 2) return a;
    if (Pow(a, (Mod - 1) / 2, Mod) != 1) {
        puts("No square");
        return -1;
    }
    while (tp % 2 == 0) {
        S++;
        tp /= 2;
    }
    long long Q = tp, z;
    for (int i = 2;; i++) {
        if (Pow(i, (Mod - 1) / 2, Mod) != 1) {
            z = i;
            break;
        }
    }
    long long M = S, c = Pow(z, Q, Mod), t = Pow(a, Q, Mod), R = Pow(a, (Q + 1) / 2, Mod);
    while (1) {
        if (t == 0)return 0;
        if (t == 1)return R;
        long long tt = t, i = 0;
        while (tt != 1) {
            tt = tt * tt%Mod; i++;
        }
        long long b = c;
        for (int j = 0; j < M - i - 1; j++) {
            b = b * b%Mod;
        }
        M = i;
        c = b * b%Mod;
        t = t * b%Mod*b%Mod;
        R = R * b%Mod;
    }
}
