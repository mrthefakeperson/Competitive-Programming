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

using namespace std;

bool swamps[205][205];
bool accRow[205];
bool combine[205];
int main()
{
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);

    int n,m;scanf("%i%i",&n,&m);
    int accMax=0;
    for(int e=0;e<n;e++)
    {
        for(int ee=0;ee<m;ee++)
        {
            char cc;scanf(" %c",&cc);
            swamps[e][ee]=(cc=='X');
            accMax= !swamps[e][ee];
            //printf("%i",swamps[e][ee]);
        }
        //printf("\n");
    }
    //int accMax=1;
    for(int e=0;e<n;e++)
    {
        //clear
        for(int ee=0;ee<m;ee++) accRow[ee]=swamps[e][ee];
        for(int ee=e+1;ee<n;ee++)
        {
            for(int eee=0;eee<m;eee++)
            {
                accRow[eee]=accRow[eee] || swamps[ee][eee];
            }
            //combine
            for(int eee=0;eee<m;eee++)
            {
                combine[eee]=swamps[e][eee] || swamps[ee][eee];
            }
            //sweep
            int lastFree=0;
            for(int eee=0;eee<m;eee++)
            {
                if(combine[eee]) lastFree=eee+1;
                while(lastFree<eee && accRow[lastFree]) lastFree++;
                if(!combine[eee] && !accRow[eee]){
                    if((eee-lastFree+1)*(ee-e+1)>accMax){
                        accMax=(eee-lastFree+1)*(ee-e+1);
                        //printf("found rows %i,%i from %i to %i: %i\n",e,ee,lastFree,eee,accMax);
                    }
                }
                    //accMax=max(accMax,(eee-lastFree+1)*(ee-e+1));
            }
        }
    }
    printf("%i\n",accMax);

	return 0;
}