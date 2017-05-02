#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int ll[300000],fw[300000];
int main()
{
    freopen("262144.in","r",stdin);
    freopen("262144.out","w",stdout);
    
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        scanf("%i",&ll[e]);
        fw[e]= -1;
    }
    let accMax=0;
    for(let e=0;e<61;e++)
    {
        for(let ee=0;ee<n;ee++)
        {
            if(ll[ee]==e){
                fw[ee]=ee;
                accMax=e;
            }
            else if(fw[ee]!= -1){
                if(fw[ee]+1<n && fw[fw[ee]+1]!= -1){
                    fw[ee]=fw[fw[ee]+1];
                    accMax=e;
                }
                else{
                    fw[ee]= -1;
                }
            }
        }
    }
    printf("%i\n",accMax);

	return 0;
}