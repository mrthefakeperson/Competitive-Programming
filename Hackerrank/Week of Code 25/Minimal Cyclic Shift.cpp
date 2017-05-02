#include <bits/stdc++.h>
#define let auto

using namespace std;

const int M = 998244353;
int n,k;
int a[100005], b[100005];
void differences(int* start, int* finish)
{
    for(int* e = start; e < finish; e++) {
        *e = (*(e+1) - *e + M) % M;
    }
}
void differences2(int* start, int* finish)
{
    int x = *start;
    for(int* e = start; e < finish-1; e++) {
        *e = (*(e+1) - *e + M) % M;
    }
    *(finish-1) = (x - *(finish-1) + M) % M;
}
int main()
{
    scanf("%i%i", &n, &k);
    for(int e = 0; e < n; e++) {
        scanf("%i", &a[e]);
    }
    for(int e = 0; e < n; e++) {
        scanf("%i", &b[e]);
    }
    for(int e = 0; e < k+1; e++) {
        differences(a, a+n-1-e);
        differences2(b, b+n);
    }
    bool fl;
    for(int e = 0; e < n; e++) {
        fl = true;
        for(int ee = 0; fl && ee < n-1-k; ee++) {
            fl = fl && (a[ee] == b[(e+ee)%n]);
        }
        if (fl) {
            printf("%i\n", e);
            break;
        }
    }
    if (!fl) printf("-1\n");
}