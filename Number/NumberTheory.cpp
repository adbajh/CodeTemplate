#include <bits/stdc++.h>
#define _N2 (int)(2e6 + 1e3)
typedef long long ll;
typedef __int128_t lll;
typedef std::map<ll,int> FACT;
using namespace std;
std::random_device seed;
std::mt19937 gen(seed());

/***** 素数筛 *****/

int MaxN;
int Prime[_N2], prime_fac[_N2], prime_cnt;
bool isPrime[_N2];

void Euler(int n) {
    MaxN = n;
    for (int i = 1; i <= n; i++) isPrime[i] = true;
    prime_cnt = 0;
    int prod = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            Prime[prime_cnt++] = i;
            prime_fac[i] = i;
        }
        for (int j = 0; j < prime_cnt && (prod = Prime[j] * i) <= n; j++) {
            isPrime[prod] = 0;
            prime_fac[prod] = Prime[j];
            if (i % Prime[j] == 0) break;
        }
    }
}

/***** 最大公约数 *****/

ll gcd(ll a, ll b) {
    ll tem;
    while (b) {
        tem = a;
        a = b;
        b = tem % b;
    }
    return a;
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll xi, yi;
    ll ret = extended_gcd(b, a%b, xi, yi);
    x = yi;
    y = xi - (a/b) * x;
    return ret;
}

/***** 带模运算 *****/

#define add(x,y,mod) (((x) + (y)) % mod)
#define mns(x,y,mod) ((((x) - (y)) % mod + mod) % mod)
#define mul(x,y,mod) (ll)((lll)(x) * (y) % mod)

ll qpow(ll a, ll x, ll mod) {
    ll ret = 1;
    for (; x; x >>= 1, a = mul(a,a,mod))
        if (x & 1) ret = mul(ret,a,mod);
    return ret;
}

/***** 素数判定 *****/

bool Miller(ll n) {
    if (n < 2) return false;
    else if (n <= MaxN) return isPrime[n];
    static const vector<ll> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    ll u = n - 1;
    int t = 0;
    while ((u&1) == 0) u >>= 1, t++;
    for (ll a : bases) {
        ll x = qpow(a,u,n);
        if (x == 1 || x == n - 1 || x == 0) continue;
        for (int i = 1; i <= t; i++) {
            x = mul(x,x,n);
            if (x == n - 1 && i != t) {
                x = 1;
                break;
            }
            if (x == 1) return false;
        }
        if (x != 1) return false;
    }
    return true;
}

/***** 分解质因数 *****/

#define g(x,c,mod) (ll)(((lll)x * x + c) % mod)

ll Pollard(ll n) {
    ll l, r, c, d, prod, k, i;
    std::uniform_int_distribution<ll> Rand(1,n-1);
    l = 0, r = 0;
    c = Rand(gen);
    prod = 1;
    for (k = 1;;k <<= 1, l = r, prod = 1) {
        for (i = 1; i <= k; i++) {
            r = g(r,c,n);
            prod = mul(prod,abs(r-l),n);
            if (!(i%127)) {
                d = gcd(prod,n);
                if (d > 1) return d;
            }
        }
        d = gcd(prod,n);
        if (d > 1) return d;
    }
}

void factorization(ll n, FACT &factors) {
    if (n == 1) return;
    else if (n <= MaxN) {
        while (n > 1) {
            int fac = prime_fac[n];
            n /= fac;
            factors[fac]++;
        }   
    }
    else {
        if (Miller(n)) factors[n]++;
        else {
            ll n1 = Pollard(n);
            factorization(n/n1,factors);
            factorization(n1,factors);
        }
    }
}

// tests

void test_Miller() {
    std::uniform_int_distribution<int> R1(0,prime_cnt - 1);
    for (int i = 0; i < 20; i++) {
        ll p1 = Prime[R1(gen)], p2 = Prime[R1(gen)];
        ll n = p1 * p2;
        printf("%lld = %lld * %lld, Pollard = %lld.\n", n, p1, p2, Pollard(n));
    }
}

void fac2str(const FACT &fac, int z, string &str) {
    str.clear();
    str.push_back('1');
    for (auto &[p,e] : fac) {
        int E = e % z;
        if (E != 0) {
            str.push_back('*');
            str += to_string(p);
            str.push_back('^');
            str += to_string(E);
        }
    }
}

void complement(const FACT &src, int z, FACT &dst) {
    dst.clear();
    for (auto &[p,e] : src) {
        int E = e % z;
        if (E != 0) dst[p] = z - E;
    }
}

void test1() {
    ll a = 25, b = 18, x, y;
    ll d = extended_gcd(a,b,x,y);
    printf("%lld %lld %lld\n",d,x,y);
}

void test2() {
    Euler((int)2e6);
    int n, z;
    scanf("%d%d", &n, &z);
    ll arr[n];
    FACT fac[n];
    string str[n];
    unordered_map<string, int> MAP;
    for (int i = 0; i < n; i++) {
        fac[i].clear();
        scanf("%lld", &arr[i]);
        factorization(arr[i],fac[i]);
        fac2str(fac[i],z,str[i]);
        MAP[str[i]]++;
    }
    ll count;
    ll sum = 0;
    string cur;
    FACT fact, comp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            fact.clear();
            for (auto &[p,e] : fac[i]) fact[p] += e;
            for (auto &[p,e] : fac[j]) fact[p] += e;
            complement(fact,z,comp);
            fac2str(comp,z,cur);
            auto it = MAP.find(cur);
            if (it == MAP.end()) count = 0;
            else count = it->second;
            if (cur == str[i]) count--;
            if (cur == str[j]) count--;
            sum += count;
        }
    }
    sum /= 3;
    printf("%lld\n",sum);
}

int main() {
    test1();
    return 0;
}