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
	int h=fData.size()-1; //looks at the outter most level, giving height
//WARNING: ASSUMES ALL ROWS ARE THE SAME WIDTH
	int w=fData[0].size()-1; //looks at an inner-level, giving width
	int i=0;
	int j=0;
	string Path;
	string PathReward;
	int Reward=0;

	if (minmax == "min")
	{
		cout << "Alg1 MIN on " << h << " x " << w <<endl;
		while ((i !=w) && (j !=h))
		{
			cout << endl << "Current Reward: " << Reward << endl;
			cout << j << "," << i << ": ";
			if (i+1<= w)
			{
				if (j+1<=h)
				{
					if (fData[i+1][j]<fData[i][j+1])
					{
						cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go RIGHT.\n ";
						Path.append("R");
						i++;
						Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
						PathReward += fData[i][j] + "+";
					}
					else
					{
						cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go UP.\n";
						Path.append("U");
						j++;
						Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
						PathReward += fData[i][j] + "+";
					}
				}
				else //j+1>h
				{
					cout << "I cannot increase j any more. j = " << j << " so I'm FORCED to go RIGHT (+"<<fData[i+1][j]<<")\n";
					Path.append("R");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j] + "+";	
				}
			}
			else //i+1>w
			{
				cout << "I cannot increase i any more. i = " << i << " so I'm FORCED to go UP (+"<<fData[i][j+1]<<")\n";
				if (j+1<=w)
				{
					Path.append("U");
					j++;
					Reward += fData[i][j];
					PathReward += fData[i][j] + "+";
				}
				else //this should never be reached because j=h and i=w should break out of the while loop.
				{
					cout << "Hit error statement 1\nj,i = " << j << "," << i << "\nh,w = " << h << "," << w;
				}
			}
		}
	}
	//else //if minmax =/= "min" then I assume it means max. I don't want to reprompt the user for a valid input.
	//{
	//	cout << "Alg1 MAX\n";
	//	while ((i !=h) && (j !=w))
	//	{
	//		cout << j << "," << i << ": ";
	//		if (i+1<= h) //(NEED TO CHECK BOTH BOUNDS, DUMMY)
	//		{
	//			if (fData[i+1][j]>fData[i][j+1])
	//			{
	//				cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go UP.\n";
	//				Path.append("U");
	//				i++;
	//				Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
	//				PathReward += fData[i][j] + "+";	
	//			}
	//			else if (j+1<=w)
	//			{
	//				cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go RIGHT.\n";
	//				Path.append("R");
	//				j++;
	//				Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
	//				PathReward += fData[i][j] + "+";
	//			}
	//			else
	//			{
	//				cout << "I cannot increase j any more. j = " << j << "so I'm FORCED to go UP.\n";
	//				Path.append("U");
	//				i++;
	//				Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
	//				PathReward += fData[i][j] + "+";	
	//			}
	//		}
	//		else //if increasing i would go off the grid
	//		{
	//			cout << "I cannot increase i any more. i = " << i << " so I'm FORCED to go RIGHT.\n";
	//			if (j+1<=w)
	//			{
	//				Path.append("R");
	//				j++;
	//				Reward += fData[i][j];
	//				PathReward += fData[i][j] + "+";
	//			}
	//			else //this should never be reached because i=h and j=w should break out of the while loop.
	//			{
	//				cout << "Hit error statement 2\ni,j = " << i << "," << j << "\nh,w = " << h << "," << w;
	//			}
	//		}
	//	}
	//}
	PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	cout << "End reached! Reward: " + Reward << "\nPath taken: " << Path;
	return;
}
