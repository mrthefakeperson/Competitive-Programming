#include <bits/stdc++.h>

#define _ make_pair

using namespace std;

long long hash_(pair<int, int> x) {return ((long long)x.first << 32) + x.second; }
pair<int, int> remove_(int i, int sq)
{
    int e = (sq >> i) & 1;
    int side = sq & ((1 << i) - 1);
    int otherSide = sq >> (i+1);
    return _(e, (otherSide << i) + side);
}
double visited1[1 << 25];
unordered_map<long long, double> visited2;
const int C = 24;
double visited(int a, int b)
{
    if (a <= C) return visited1[(1 << a) + b];
    else {
        if (visited2.find(hash_(_(a, b))) == visited2.end())
            return -1.;
        else
            return visited2[hash_(_(a,b))];
    }
}
void setVisited(int a, int b, double c)
{
    if (a <= C) visited1[(1 << a) + b] = c;
    else visited2[hash_(_(a,b))] = c;
}
int n, k;
double f(int len, int sequence)
{
    if (n - len == k) return 0.;
    else {
        if (visited(len, sequence) == -1) {
            double acc = 0.;
            for (int e = 0; e < len/2; e++) {
                auto a = remove_(e, sequence);
                double aa = f(len-1, a.second) + a.first;
                auto b = remove_(len-1-e, sequence);
                double bb = f(len-1, b.second) + b.first;
                acc += max(aa, bb);
            }
            if (len % 2 == 0)
                acc /= len/2.;
            else {
                auto a = remove_(len/2, sequence);
                acc = (2.*acc + a.first + f(len-1, a.second)) / len;
            }
            setVisited(len, sequence, acc);
        }
        return visited(len, sequence);
    }
}
int main()
{
    for (int e = 0; e < (1 << 25); e++) visited1[e] = -1;
    scanf("%i%i", &n, &k);
    int initialSequence = 0;
    for (int e = 0; e < n; e++) {
        char c; scanf(" %c", &c);
        if (c == 'W') {
            initialSequence += 1 << e;
        }
    }
    printf("%f\n", f(n, initialSequence));
}