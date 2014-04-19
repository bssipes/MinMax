#include <string>
#include <iostream>
#include <vector>
using namespace std;
/*
Overall, there are 4 options.
CHOOSE to go UP
CHOOSE to go RIGHT
FORCED to go UP
FORCED to go RIGHT
*/
void alg1(string minmax, vector<vector<int> > fData) //Greedy - Immediate Neighbor
{
	int h = 4; //0 through 4 = 5 entries
	int w = 4;//0 through 4 = 5 entries
	int i=0;
	int j=0;
	string Path;
	string PathReward;
	int Reward;

	if (minmax == "min")
	{
		while ((i !=h) && (j !=w))
		{
			if (i+1<= h)
			{
				if (fData[i+1][j]<fData[i][j+1])
				{
					cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go UP.";
					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j] + "+";	
				}
				else if (j+1<=w)
				{
					cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go RIGHT.";
					Path.append("R");
					j++;
					Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
					PathReward += fData[i][j] + "+";
				}
				else
				{
					cout << "I cannot increase j any more. j = " << j << "so I'm FORCED to go UP.";
					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j] + "+";	
				}
			}
			else //if increasing i would go off the grid
			{
				cout << "I cannot increase i any more. i = " << i << " so I'm FORCED to go RIGHT.";
				if (j+1<=w)
				{
					Path.append("R");
					j++;
					Reward += fData[i][j];
					PathReward += fData[i][j] + "+";
				}
				else //this should never be reached because i=h and j=w should break out of the while loop.
				{
					cout << "Hit error statement 1\ni,j = " << i << "," << j << "\nh,w = " << h << "," << w;
				}
			}
		}
	}
	else //if minmax =/= "min" then I assume it means max. I don't want to reprompt the user for a valid input.
	{
		while ((i !=h) && (j !=w))
		{
			if (i+1<= h)
			{
				if (fData[i+1][j]>fData[i][j+1])
				{
					cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go UP.";
					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j] + "+";	
				}
				else if (j+1<=w)
				{
					cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go RIGHT.";
					Path.append("R");
					j++;
					Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
					PathReward += fData[i][j] + "+";
				}
				else
				{
					cout << "I cannot increase j any more. j = " << j << "so I'm FORCED to go UP.";
					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j] + "+";	
				}
			}
			else //if increasing i would go off the grid
			{
				cout << "I cannot increase i any more. i = " << i << " so I'm FORCED to go RIGHT.";
				if (j+1<=w)
				{
					Path.append("R");
					j++;
					Reward += fData[i][j];
					PathReward += fData[i][j] + "+";
				}
				else //this should never be reached because i=h and j=w should break out of the while loop.
				{
					cout << "Hit error statement 1\ni,j = " << i << "," << j << "\nh,w = " << h << "," << w;
				}
			}
		}
	}
	PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	cout << "End reached! Reward: " + Reward << "\nPath taken: " << Path;
	return;
}
