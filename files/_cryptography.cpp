#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

bool sieve[32000];
vector<int> primes;
int nodes[100005];
int countDivisions(int a,int nn)
{
    let acc=0;
    while(a%nn==0)
    {
        acc++;
        a/=nn;
    }
    return acc;
}
vector<int> codes[100005];
void code(int i)
{
    for(let prime:primes)
    {
        let aa=countDivisions(nodes[i],prime);
        if(aa!=0){
            codes[i].push(prime);
            codes[i].push(aa);
        }
    }
}
bool compare(int l,int r)
{
    code(l);code(r);return codes[l]<codes[r];
}
int solveMe(int l,int r)  //right node of edge
{
    let m=(l+r)/2;
    if(l+1==r) return r;
    if(compare(m-1,m)) return solveMe(l,m);
    else return solveMe(m,r);
}
int main()
{
    for(let e=2;e<32000;e++)
    {
        if(!sieve[e]){
            primes.push(e);
            for(let ee=e;ee<32000;ee+=e)
                sieve[ee]=true;
        }
    }
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        scanf("%i",&nodes[e]);
    }
    printf("%i\n",solveMe(0,n));
    
	return 0;
}
