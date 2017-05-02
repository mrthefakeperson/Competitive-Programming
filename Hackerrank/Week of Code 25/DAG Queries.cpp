#include <bits/stdc++.h>
#define let auto

using namespace std;

vector<int> adj[100005];
vector<int> visitable[100005];
bool visited[100005];
void getVisitable(int n)
{
    if (!visited[n]) {
        unordered_set<int> s;
        visited[n] = true;
        visitable[n].push_back(n);
        for (let e: adj[n]) {
            getVisitable(e);
            for (let ee: visitable[e]) {
                if (s.find(ee) == s.end()) {
                    visitable[n].push_back(ee);
                    s.insert(ee);
                }
            }
        }
    }
}
int values[100005];
int main()
{
    int n, m, q; scanf("%i%i%i", &n, &m, &q);
    for (let e = 0; e < m; e++) {
        int a, b; scanf("%i%i", &a, &b); a--; b--;
        adj[a].push_back(b);
    }
    for (let e = 0; e < n; e++) getVisitable(e);
    /*
    for (let e = 0; e < n; e++) {
        for (let ee: visitable[e])
            printf("%i ", ee);
        printf("\n");
    }
    */
    for (let e = 0; e < q; e++) {
        int a; scanf("%i", &a);
        if (a==1) {
            int u, x; scanf("%i%i", &u, &x); u--;
            for (let ee: visitable[u])
                values[ee] = x;
        }
        else if (a==2) {
            int u, x; scanf("%i%i", &u, &x); u--;
            for (let ee: visitable[u])
                values[ee] = min(x, values[ee]);
        }
        else if (a==3) {
            int u; scanf("%i", &u); u--;
            printf("%i\n", values[u]);
        }
    }
}