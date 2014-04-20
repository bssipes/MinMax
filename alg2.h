/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014

Algorithm 2: Greedy- Min/Max Values of Array
Make a copy of the array and sort it by value
Go directly to the largest value 
(option 1: all right until correct column, then up to correct row)
(option 2: all up until correct row, then right to correct column)
Go to next largest (target[i] >= current[i] and target[j] >= current[j]) by the same option

Overall, there are 4 options.
CHOOSE to go RIGHT
CHOOSE to go UP
FORCED to go UP
FORCED to go RIGHT
*/

#include <string>
#include <iostream>
#include <vector>
#include "choose.h"
using namespace std;

void alg1(bool min, vector<vector<int> > fData) //Greedy - Min/Max of entire grid
{
	int h=fData.size()-1; //looks at the outter most level, giving height
//WARNING: ASSUMES ALL ROWS ARE THE SAME WIDTH
	int w=fData[0].size()-1; //looks at an inner-level, giving width
	int i=0;
	int j=0;
	string Path = "";
	string PathReward = "";
	int Reward=0;
	char choice;

	if (min == true)
	{
		cout << "\nAlg2 MIN on " << h << " x " << w <<endl;
	}
	else
	{
		cout << "\nAlg2 MAX on " << h << " x " << w <<endl;
	}
	PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	cout << endl << "End reached! Reward: " << Reward << "\nPath taken: " << Path << endl;
	return;
}
