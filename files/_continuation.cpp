#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto


using namespace std;

const long long MOD=1000000007;
long long adj[50][101][101];
bool adj2[50][101][101];
int main()
{
    int n,m,q;scanf("%i%i%i",&n,&m,&q);
    for(let e=0;e<m;e++)
    {
        int a,b;scanf("%i%i",&a,&b);a--;b--;
        adj[0][a][b]++;
        adj2[0][a][b]=true;
    }
    for(let e=1;e<45;e++)
    {
        for(let x=0;x<n;x++)
        {
            for(let y=0;y<n;y++)
            {
                for(let a=0;a<n;a++)
                {
                    adj[e][x][y]+=adj[e-1][x][a]*adj[e-1][a][y];
                    adj[e][x][y]%=MOD;
                    adj2[e][x][y]=adj2[e][x][y] || (adj[e-1][x][a] && adj[e-1][a][y]);
                }
            }
        }
    }
    for(let e=0;e<q;e++)
    {
        long long k;scanf("%lld",&k);k--;
        vector<pair<long long,int> > ans,___;
        ans.resize(n);
        for(let ee=0;ee<n;ee++) ans[ee]=_(1,ee);
        for(let ee=0;ee<n;ee++) ___.push(_(0,999999));
        for(let bit=0;bit<45;bit++)
        {
            if(((1LL<<bit) & k) != 0){
                let nAns=___;
                for(let x=0;x<n;x++)
                {
                    for(let y=0;y<n;y++)
                    {
                        if(adj2[bit][x][y]){
                            //ans[x] to nAns[y]
                            if(ans[x].snd>nAns[y].snd){
                            }
                            else if(ans[x].snd<nAns[y].snd){
                                nAns[y]=_(ans[x].fst*adj[bit][x][y]%MOD,ans[x].snd);
                            }  
                            else if(ans[x].snd==nAns[y].snd){
                                nAns[y]=_((ans[x].fst*adj[bit][x][y]+nAns[y].fst)%MOD,ans[x].snd);
                            }
                        }
                    }
                }
                ans=nAns;
        //for(let ee=0;ee<n;ee++) printf("%lld,%i ",ans[ee].fst,ans[ee].snd);
        //printf("\n");
            }
        }
        for(let ee=0;ee<n;ee++) printf("%lld ",ans[ee].fst);
        printf("\n");
    }

	return 0;
}
