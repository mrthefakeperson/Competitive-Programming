#include <bits/stdc++.h>

using namespace std;

int colour[1005][1005];
int xmin[1000005], ymin[1000005], xmax[1000005], ymax[1000005];
int sw[1005][1005];
bool used[1000005];
bool oneColour[1000005];
int main()
{
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);
    int n; scanf("%i", &n);
    for (int e = 1; e <= n*n; e++) {
        xmin[e] = 99999999;
        ymin[e] = 99999999;
    }
    for (int e = 0; e < n; e++) {
        for (int ee = 0; ee < n; ee++){
            int k; scanf("%i", &k);
            colour[e][ee] = k;
            xmin[k] = min(xmin[k], e);
            xmax[k] = max(xmax[k], e);
            ymin[k] = min(ymin[k], ee);
            ymax[k] = max(ymax[k], ee);
            oneColour[k] = true;
        }
    }
    for (int e = 1; e <= n*n; e++) {
        if (xmin[e] == 99999999){}
        else {
            sw[xmin[e]+1][ymin[e]+1]++;
            sw[xmin[e]+1][ymax[e]+2]--;
            sw[xmax[e]+2][ymin[e]+1]--;
            sw[xmax[e]+2][ymax[e]+2]++;
        }
    }
    for (int e = 1; e <= n; e++) {
        for (int ee = 1; ee <= n; ee++) {
            sw[e][ee] += sw[e-1][ee];
            sw[e][ee] += sw[e][ee-1];
            sw[e][ee] -= sw[e-1][ee-1];
            if (sw[e][ee] > 1)
                used[colour[e-1][ee-1]] = true;
        }
    }
    int acc = 0;
    for (int e = 1; e <= n*n; e++)
        if (!used[e]) acc++;
    int d = 0;
    for (int e = 1; e <= n*n; e++)
        if (oneColour[e]) d++;
    if (d == 1 && n != 1) acc--;
    printf("%i\n", acc);
}