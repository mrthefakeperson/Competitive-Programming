#include <bits/stdc++.h>

char __;
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(__=getchar()); x=(x<<3)+(x<<1)+__-'0');}while(0)

using namespace std;
const int SQ = 317;
inline int group(int x) { return x / SQ; }
const int QR = 18;
inline int microGroup(int x) { return x / 5556; }

//vector<pair<int, int> > points;
vector<pair<int, int> > points[SQ];
//vector<int> _micro[SQ];
vector<int> _micro[SQ][QR];

void microUpdate(int g, int y)
{
    _micro[g][microGroup(y)].push_back(y);
}
int microQuery(int g, int y)
{
    int k = microGroup(y);
    int acc = 0;
    if (k < 9) {
        acc = points[g].size();
        for (int e = 0; e <= k; e++)
            acc -= _micro[g][e].size();
    }
    else {
        for (int e = k + 1; e < QR; e++) {
            acc += _micro[g][e].size();
        }
    }
    for (int e: _micro[g][k])
        if (e > y) acc++;
    return acc;
}
int microQuery2(int g, int y)
{
    int k = microGroup(y);
    int acc = 0;
    if (k < 9) {
        for (int e = 0; e < k; e++) {
            acc += _micro[g][e].size();
        }
    }
    else {
        acc = points[g].size();
        for (int e = k; e < QR; e++) {
            acc -= _micro[g][e].size();
        }
    }
    for (int e: _micro[g][k])
        if (e < y) acc++;
    return acc;
}
void macroUpdate(int x, int y)
{
    points[group(x)].push_back(make_pair(x, y));
    microUpdate(group(x), y);
}
int macroQuery(int x, int y)
{
    int acc = 0;
    for (int e = 0; e < group(x); e++) {
        acc += microQuery(e, y);
    }
    for (int e = group(x)+1; e < SQ; e++) {
        acc += microQuery2(e, y);
    }
    for (pair<int, int> e: points[group(x)]) {
        int xx = e.first, yy = e.second;
        if ((xx > x && yy < y) || (xx < x && yy > y))
            acc++;
    }
    return acc;
}

int plA[100005];
int plB[100005];
int main()
{
    freopen("friendcross.in", "r", stdin);
    freopen("friendcross.out", "w", stdout);
    
    int n, k; //scanf("%i%i", &n, &k);
    scan(n); scan(k);
    for (int e = 0; e < n; e++) {
        int x; //scanf("%i", &x);
        scan(x);
        plA[x] = e;
    }
    for (int e = 0; e < n; e++) {
        int x; //scanf("%i", &x);
        scan(x);
        plB[x] = e;
    }
    long long acc = 0LL;
    for (int e = 1; e < n; e++) {
        int x = plA[e], y = plB[e];
        acc += macroQuery(x, y);
        if (e-k >= 1) {
            int xx = plA[e-k], yy = plB[e-k];
            macroUpdate(xx, yy);
        }
    }
        int x = plA[n], y = plB[n];
        acc += macroQuery(x, y);
    printf("%lld\n", acc);
}