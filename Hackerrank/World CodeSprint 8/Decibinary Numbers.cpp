#include <bits/stdc++.h>

using namespace std;
const int MAX = 290000, MAX2 = 18;

long long visited[MAX+1][MAX2+1];
long long put_(int x, int here)
{
    if (x < 0) return 0LL;
    else if (x == 0 && here == -1) return 1LL;
    else if (here == -1) return 0LL;
    else return visited[x][here];
}
long long put(int x, int here)
{
    long long acc = 0LL;
    for (int e = 0; e < 10; e++) {
        acc += put_(x-e*(1 << here), here-1);
    }
    return acc;
}
long long pw(long long a, int b)
{
    if (b == 0) return 1LL;
    else return a * pw(a, b-1);
}
long long numbers[MAX];
int fnd(int l, int r, long long x)
{
    if (l == r) return l;
    else {
        int h = (l+r) / 2;
        if (numbers[h] < x)
            return fnd(h+1, r, x);
        else
            return fnd(l, h, x);
    }
}
long long kthLargest(int x, int here, long long k)
{
    if (here == -1) return 0LL;
    else {
        long long acc = k;
        int e_ = 9;
        for (; e_ >= 0; e_--) {
            long long e = put_(x-e_*(1 << here), here-1);
            if (acc < e)
                break;
            else
                acc -= e;
        }
        int e = e_;
        return e * pw(10LL, here) + kthLargest(x-e*(1 << here), here-1, acc);
    }
}
long long answerQuery(long long n)
{
    int p = fnd(0, MAX-1, n);
    return kthLargest(p, MAX2, numbers[p]-n);
}
int main()
{
    for (int x = 0; x <= MAX; x++)
        for (int here = 0; here <= MAX2; here++)
            visited[x][here] = put(x, here);
    for (int e = 0; e < MAX; e++)
        numbers[e] = visited[e][MAX2];
    for (int e = 1; e < MAX; e++)
        numbers[e] += numbers[e-1];
    
    int q; scanf("%i", &q);
    for (int e = 0; e < q; e++) {
        long long n; scanf("%lld", &n);
        printf("%lld\n", answerQuery(n));
    }
}
