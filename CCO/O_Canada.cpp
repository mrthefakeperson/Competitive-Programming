#include <bits/stdc++.h>
#define let auto
#define push push_back

using namespace std;

int n;
vector<vector<int> > grids[10005];
void lexFlip(int i)
{
    for(let e=0;e<n-1;e++)
    {
        for(let ee=0;ee<n-1;ee++)
        {
            if(!grids[i][e][ee]){
                grids[i][e][ee]^=1;
                grids[i][e+1][ee]^=1;
                grids[i][e][ee+1]^=1;
                grids[i][e+1][ee+1]^=1;
            }
        }
    }
}
int main()
{
    int g;scanf("%i%i",&n,&g);
    for(let e=0;e<g;e++)
    {
        for(let ee=0;ee<n;ee++)
        {
            vector<int> st;
            for(let eee=0;eee<n;eee++)
            {
                char c;scanf(" %c",&c);
                st.push(c=='R');
            }
            grids[e].push(st);
        }
    }
    for(let e=0;e<g;e++)
    {
        lexFlip(e);
    }
    sort(grids,grids+g);
    vector<vector<int> > prev;
    let accStack=0,acc=0;
    for(let e=0;e<g;e++)
    {
        if(grids[e]==prev) accStack++;
        else{
            acc+=accStack*(accStack-1)/2;
            accStack=1;
        }
        prev=grids[e];
    }
    acc+=accStack*(accStack-1)/2;
    printf("%i\n",acc);

    return 0;
}