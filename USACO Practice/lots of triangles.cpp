#include <bits/stdc++.h>

using namespace std;

const double PI = 2*acos(0.);
void prl(vector<int> ll){
    for (int e: ll) printf("%i ", e);
    printf("\n");
}
void prl(vector<double> ll){
    for (double e: ll) printf("%f ", e);
    printf("\n");
}
void prl(vector<pair<double, double> > ll){
    for (auto e: ll) printf("%f,%f ", e.first, e.second);
    printf("\n");
}

int n;
int x[305], y[305];
int answers[305];

int cnt[300], gr[20];
void countInversions(vector<double> &ll)
{
    //if (n > 50) return;
    
    for (int e = 0; e < 300; e++) cnt[e] = 0;
    for (int e = 0; e < 20; e++) gr[e] = 0;
    vector<pair<double, int> > qq;
    for (int e = 0; e < ll.size(); e++)
        qq.push_back(make_pair(ll[e], e));
    sort(qq.begin(), qq.end());
    vector<pair<int, int> > q;
    for (int e = 0; e < qq.size(); e++)
        q.push_back(make_pair(qq[e].second, e));
    sort(q.begin(), q.end());
    for (auto e_: q) {
        int v = e_.second;
        cnt[v]++;
        gr[v/20]++;
        int e = 0, acc = 0;
        for (; e+20 < v; e+=20) acc += gr[e/20];
        for (; e < v; e++) acc += cnt[e];
        answers[acc]++;
    }
    
}
double angle(int p1, int p2)
{
    auto xx = atan2(y[p2]-y[p1], x[p2]-x[p1]);
    if (xx < 0) xx += 2*PI;
    return xx;
}
pair<double, double> trigonometry(int p1, int p2, int p3)
{
    //if (n > 50) return make_pair(0,0);
    
    double aa = angle(p1, p2);
    double bb = aa-PI;
    if (bb < 0) bb += 2*PI;
    double angleA = fabs(angle(p1, p3) - aa);
    double angleB = fabs(bb - angle(p2, p3));
    if (angleA > PI) angleA = 2*PI - angleA;
    if (angleB > PI) angleB = 2*PI - angleB;
    //printf("(%i,%i),(%i,%i),(%i,%i) -> %f,%f\n", x[p1],y[p1],x[p2],y[p2],x[p3],y[p3],angleA,angleB);
    return make_pair(angleA, angleB);
}
void solve(int p1, int p2)
{
    double slope = 99999999, b = -99999999; //infinity
    if (x[p1] != x[p2]) {
        slope = (double)(y[p2]-y[p1]) / (x[p2]-x[p1]);
        b = y[p1] - slope*x[p1];
    }
    vector<int> pointsAbove, pointsBelow;
    for (int e = 0; e < n; e++) {
        if (e != p1 && e != p2) {
            bool f;
            if (x[p1] == x[p2]) {
                f = (x[e] < x[p1]);
            }
            else {
                f = (y[e] > slope*x[e]+b);
            }
            if (f) pointsAbove.push_back(e);
            else pointsBelow.push_back(e);
        }
    }
    vector<pair<double, double> > angles;
    for (int p3: pointsAbove) {
        angles.push_back(trigonometry(p1, p2, p3));
    }
    stable_sort(angles.begin(), angles.end());
    vector<double> a;
    for (auto e: angles) a.push_back(e.second);
    
    for (int e = 0; e < 300; e++) cnt[e] = 0;
    for (int e = 0; e < 20; e++) gr[e] = 0;
    vector<pair<double, int> > qq;
    for (int e = 0; e < a.size(); e++)
        qq.push_back(make_pair(a[e], e));
    stable_sort(qq.begin(), qq.end());
    vector<pair<int, int> > q;
    for (int e = 0; e < qq.size(); e++)
        q.push_back(make_pair(qq[e].second, e));
    stable_sort(q.begin(), q.end());
    for (auto e_: q) {
        int v = e_.second;
        cnt[v]++;
        gr[v/20]++;
        int e = 0, acc = 0;
        for (; e+20 < v; e+=20) acc += gr[e/20];
        for (; e < v; e++) acc += cnt[e];
        answers[acc]++;
    }
    //countInversions(a);
    angles.clear();
    for (int p3: pointsBelow) {
        angles.push_back(trigonometry(p1, p2, p3));
    }
    stable_sort(angles.begin(), angles.end());
    a.clear();
    for (auto e: angles) a.push_back(e.second);
    
    for (int e = 0; e < 300; e++) cnt[e] = 0;
    for (int e = 0; e < 20; e++) gr[e] = 0;
    qq.clear();
    for (int e = 0; e < a.size(); e++)
        qq.push_back(make_pair(a[e], e));
    stable_sort(qq.begin(), qq.end());
    q.clear();
    for (int e = 0; e < qq.size(); e++)
        q.push_back(make_pair(qq[e].second, e));
    stable_sort(q.begin(), q.end());
    for (auto e_: q) {
        int v = e_.second;
        cnt[v]++;
        gr[v/20]++;
        int e = 0, acc = 0;
        for (; e+20 < v; e+=20) acc += gr[e/20];
        for (; e < v; e++) acc += cnt[e];
        answers[acc]++;
    }
    //countInversions(a);
    //allTriangles(p1, p2, pointsAbove);
    //allTriangles(p1, p2, pointsBelow);
}
int main()
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    
    scanf("%i", &n);
    for (int e = 0; e < n; e++){
        scanf("%i%i", &x[e], &y[e]);
    }
    for (int e = 0; e < n; e++) {
        for (int ee = e+1; ee < n; ee++) {
            if (x[e] <= x[ee]) //solve line segment
                solve(e, ee);
            else
                solve(ee, e);
        }
    }
    for (int e = 0; e < n-2; e++)
        printf("%i\n", answers[e]/3);
}
