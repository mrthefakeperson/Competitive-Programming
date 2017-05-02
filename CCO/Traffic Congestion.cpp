#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int ppl[1000005];
vector<int> adj[1000005];
int sizes[1000005],ans[1000005];
void dfs_for_size(int prev,int node)
{
    sizes[node]=ppl[node];
    for(let e:adj[node])
    {
        if(e!=prev){
            dfs_for_size(node,e);
            sizes[node]+=sizes[e];
        }
    }
}
void dfs(int prev,int node)
{
    let acc=ppl[node];
    for(let e:adj[node])
    {
        acc+=sizes[e];
        ans[node]=max(ans[node],sizes[e]);
    }
    for(let e:adj[node])
    {
        if(e!=prev){
            sizes[node]=acc-sizes[e];
            dfs(node,e);
        }
    }
}
int main()
{
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
        scanf("%i",&ppl[e]);
    for(let e=0;e<n-1;e++)
    {
        int a,b;scanf("%i%i",&a,&b);
        adj[a].push(b);
        adj[b].push(a);
    }
    dfs_for_size(-1,0);
    dfs(-1,0);
    let accMin=2000000001,acci=-1;
    for(let e=0;e<n;e++)
    {
        if(ans[e]<accMin){
            acci=e;
            accMin=ans[e];
        }
    }
    printf("%i\n",acci);

	return 0;
}
