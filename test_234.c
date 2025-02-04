#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 快速幂取模
long long fast_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

// 计算最大公约数 (GCD)
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 使用扩展欧几里得算法计算模逆元
long long mod_inverse(long long a, long long mod) {
    long long m0 = mod, t, q;
    long long x0 = 0, x1 = 1;
    if (mod == 1) return 0;
    while (a > 1) {
        q = a / mod;
        t = mod;
        mod = a % mod, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// 计算 C(m, n) % p^e
long long combination_mod_pe(long long m, long long n, long long p, long long e) {
    long long pe = pow(p, e); // p^e
    long long numerator = 1, denominator = 1, count_p = 0;

    // 分子和分母逐步计算，同时统计 p 的因子数量
    for (long long i = 0; i < n; i++) {
        long long a = m - i, b = i + 1;

        // 消去分子和分母中的 p 的因子
        while (a % p == 0) {
            a /= p;
            count_p++;
        }
        while (b % p == 0) {
            b /= p;
            count_p--;
        }

        numerator = numerator * (a % pe) % pe;
        denominator = denominator * (b % pe) % pe;
    }

    // 如果分母中剩余的 p 的因子数量大于分子，则结果为 0
    if (count_p >= e) return 0;

    // 分母取模逆元
    long long denominator_inv = mod_inverse(denominator, pe);
    return numerator * denominator_inv % pe;
}

// 分解 n 为若干个 (pi, ei)
int factorize(long long n, long long primes[][2]) {
    int count = 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int e = 0;
            while (n % i == 0) {
                n /= i;
                e++;
            }
            primes[count][0] = i;
            primes[count][1] = e;
            count++;
        }
    }
    if (n > 1) {
        primes[count][0] = n;
        primes[count][1] = 1;
        count++;
    }
    return count;
}

// 使用中国剩余定理合并结果
long long crt(long long remainders[], long long mods[], int k) {
    long long prod = 1, result = 0;
    for (int i = 0; i < k; i++) prod *= mods[i];

    for (int i = 0; i < k; i++) {
        long long pp = prod / mods[i];
        result += remainders[i] * mod_inverse(pp, mods[i]) * pp;
        result %= prod;
    }
    return result;
}

// 扩展 Lucas 定理，适用于模数为合数的情况
long long combination_mod(long long m, long long n, long long p) {
    long long primes[10][2]; // 存储 p 的分解 (pi, ei)
    int k = factorize(p, primes); // 分解 p

    long long remainders[10], mods[10];
    for (int i = 0; i < k; i++) {
        long long pi = primes[i][0];
        long long ei = primes[i][1];
        long long pe = pow(pi, ei);

        remainders[i] = combination_mod_pe(m, n, pi, ei);
        mods[i] = pe;
    }

    return crt(remainders, mods, k); // 使用中国剩余定理合并结果
}

int main() {
    long long m, n, p;
    printf("请输入 m, n, p：");
    scanf("%lld %lld %lld", &m, &n, &p);

    long long result = combination_mod(m, n, p);
    printf("C(%lld, %lld) %% %lld = %lld\n", m, n, p, result);

    return 0;
}
