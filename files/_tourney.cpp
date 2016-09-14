#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int matchesWon[1048577];
int skillLookup[1048577];
int winners[1048576 * 2+1];		//store competitor number
int ans[1000000];
int competitors;

void printInfo()
{
	for (int e = 1; e <= 2 * competitors - 1; e++) printf("%i: %i with skill %i\n", e, winners[e], skillLookup[winners[e]]);
	for (int e = 1; e <= competitors; e++) printf("competitor %i won %i matches\n", e, matchesWon[e]);
}

void setMatch(int place,int n)
{
	if (place != 0 && skillLookup[winners[place]]<skillLookup[n]){
		++matchesWon[n];
		--matchesWon[winners[place]];
		winners[place] = n;
		setMatch(place / 2, n);
	}
}
void removeCompetitor(int place, int n)
{
	if (place != 0 && (winners[place] == n || winners[place]==0)){
		if (winners[place] != 0){
			//winners[place] = max(winners[place*2],winners[place*2+1]);
			if (skillLookup[winners[place * 2]]>skillLookup[winners[place * 2 + 1]]){
				++matchesWon[winners[place * 2]];
				winners[place] = winners[place * 2];
			}
			else{
				++matchesWon[winners[place * 2 + 1]];
				winners[place] = winners[place * 2 + 1];
			}
		}
		removeCompetitor(place / 2, n);
	}
}
int main()
{
	skillLookup[0] = -1;
	int exp, commands; scanf("%i%i", &exp, &commands);
	competitors = (int)(pow(2.0, exp));
	for (int e = 1; e <= competitors; e++)
	{
		int skill; scanf("%i", &skill);
		skillLookup[e] = skill;
		setMatch(e + competitors - 1, e);
	}

	//printInfo();

	for (int e = 0; e < commands; e++)
	{
		char which; scanf(" %c", &which);
		//printf("::%c", which);
		int a, b;
		if (which == 'R'){
			scanf("%i%i", &a, &b);
			matchesWon[a] = 0;
			skillLookup[a] = b;
			winners[a + competitors - 1] = 0;
			removeCompetitor(a + competitors - 1, a);
			setMatch(a + competitors - 1, a);
			ans[e] = -100;
			//printInfo();
		}
		else if (which == 'W'){
			ans[e] = winners[1];
			//printf("%i", winners[1]);
		}
		else{
			scanf("%i", &a);
			ans[e] = matchesWon[a]-1;
			//printf("\n\n%i;\n\n", matchesWon[a]-1);
		}
	}
	for (int e = 0; e < commands; e++)
		if (ans[e] != -100) printf("%i\n", ans[e]);

	//scanf(" ");
}