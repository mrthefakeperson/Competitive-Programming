#include <bits/stdc++.h>

using namespace std;

int P[1005], J[1005];
int answer[1005][1005][15];
int pick(int a, int b, int k)
{    
    if (k == 0) return 1;
    if (a < 0 || b < 0) return 0;
    if (answer[a][b][k] != -1) {
        return answer[a][b][k];
    }
    answer[a][b][k] = 0;
    answer[a][b][k] += pick(a-1, b, k);
    answer[a][b][k] += pick(a, b-1, k);
    answer[a][b][k] %= 1000000009;
    answer[a][b][k] -= pick(a-1, b-1, k);
    answer[a][b][k] = (answer[a][b][k] + 1000000009) % 1000000009;
    if (J[a] > P[b])
        answer[a][b][k] += pick(a-1, b-1, k-1);
    answer[a][b][k] %= 1000000009;
    //printf("%i,%i,%i -> %i\n", a, b, k, answer[a][b][k]);
    return answer[a][b][k];
}
int main()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    
    int n, m, k; scanf("%i%i%i", &n, &m, &k);
    for (int e = 0; e < n; e++)
        scanf("%i", &J[e]);
    for (int e = 0; e < m; e++)
        scanf("%i", &P[e]);
    sort(J, J+n);
    sort(P, P+m);
    for (int e = 0; e < n; e++)
        for (int ee = 0; ee < m; ee++)
            for (int eee = 0; eee <= k; eee++)
                answer[e][ee][eee] = -1;
    printf("%i\n", pick(n-1, m-1, k));
}
