#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int edges[200005];
vector<int> adj[200005];
bool visited[200005];
vector<int> rr;
void getCycle(int prev,int n)
{
    visited[n]=true;
    for(let e:adj[n])
    {
        if(visited[e]){
            rr.clear();
            rr.push(e);
            rr.push(n);return;
        }
        else{
            getCycle(n,e);
            if(rr.size()>=2 && rr[0]!=rr[rr.size()-1])
                rr.push(n);
            return;
        }
    }
}
const int MOD=1000000007;
int pow_(int b,int x)
{
    if(x==0) return 1;
    if(x%2==1) return 1LL*pow_(b,x-1)*b%MOD;
    else{
        let h=pow_(b,x/2);
        return 1LL*h*h%MOD;
    }
}
int main()
{
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        scanf("%i",&edges[e]); edges[e]--;
        adj[e].push(edges[e]);
    }
    long long acc=0,cyclePossibilities=1,remainingLength=n;
    for(let node=0;node<n;node++)
    {
        if(!visited[node]){
            rr.clear();
            getCycle(-1,node);
            if(rr[0]==rr[rr.size()-1]){
                //for(let e:rr) printf("%i ",e);printf("\n");
                let length=rr.size()-1;
                remainingLength-=length;
                acc=(acc+2LL*pow_(2,remainingLength)*cyclePossibilities)%MOD;
                cyclePossibilities=(cyclePossibilities*(pow_(2,length)-2)+MOD)%MOD;
                //printf("%i %i %i %i\n",node,acc,remainingLength,cyclePossibilities);
            }
        }
    }
    printf("%I64d\n",(((long long)pow_(2,n)-acc)%MOD+MOD)%MOD);

	return 0;
}
