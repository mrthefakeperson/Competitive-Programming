#include <bits/stdc++.h>

using namespace std;
const int SQ = 400;
inline int group(int x) { return x / SQ; }

vector<int> values[500];
void update(int x)
{
    values[group(x)].push_back(x);
}
int query(int x)
{
    int acc = 0;
    for (int e = 0; e < group(x); e++)
        acc += values[e].size();
    for (int e: values[group(x)])
        if (e < x) acc++;
    return acc;
}
void reset()
{
    for (int e = 0; e < 500; e++) values[e].clear();
}
long long countInversions(vector<int> * ll)
{
    reset();
    long long acc = 0LL;
    int len = ll -> size();
    for (int e = len-1; e >= 0; e--) {
        acc += query((*ll)[e]);
        update((*ll)[e]);
    }
    return acc;
}
int place[100005];
long long answer(int n, vector<int> * a, vector<int> * b)
{
    for (int e = 0; e < n; e++) {
        place[(*a)[e]] = e;
    }
    vector<int> mapping;
    vector<pair<int, int> > map2;
    for (int e = 0; e < n; e++) {
        mapping.push_back(place[(*b)[e]]);
        map2.push_back(make_pair(-place[(*b)[e]], e));
    }
    long long v = countInversions(&mapping);
    long long accMin = v;
    sort(map2.begin(), map2.end());
    for (pair<int, int> e: map2) {
        int i = e.second;
        v = v + i - (n - i - 1);
        //printf("%i %i\n", i, v);
        accMin = min(accMin, v);
    }
    return accMin;
}
int main()
{
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
    
    int n; scanf("%i", &n);
    vector<int> a, b;
    for (int e = 0; e < n; e++) {
        int x; scanf("%i", &x);
        a.push_back(x);
    }
    for (int e = 0; e < n; e++) {
        int x; scanf("%i", &x);
        b.push_back(x);
    }
    printf("%lld\n", min(answer(n, &a, &b), answer(n, &b, &a)));
}