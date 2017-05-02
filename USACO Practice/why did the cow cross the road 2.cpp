#include <bits/stdc++.h>

using namespace std;

int place[100005];
vector<int> adj[100005];
int main()
{
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    
    int n; scanf("%i", &n);
    for (int e = 0; e < n; e++) {
        int x; scanf("%i", &x); x--;
        place[x] = e;
    }
    for (int e = 0; e < n; e++) {
        int x; scanf("%i", &x); x--;
        for (int ee = max(x-4, 0); ee <= min(x+4, n-1); ee++) {
            adj[e].push_back(place[ee]);
        }
        sort(adj[e].begin(), adj[e].end());
        reverse(adj[e].begin(), adj[e].end());
    }
    vector<int> answers; answers.push_back(-1);
    for (int e = 0; e < n; e++) {
        for (int x: adj[e]) {
            int place = lower_bound(answers.begin(), answers.end(), x) - answers.begin() - 1;
            //printf("%i %i\n", x, place);
            if (place+1 == answers.size()) {
                answers.push_back(x);
            }
            else {
                answers[place + 1] = min(answers[place + 1], x);
            }
        }
        //for (int ee: answers) printf("%i, ", ee);
        //printf("\n");
    }
    printf("%i\n", answers.size() - 1);
}
