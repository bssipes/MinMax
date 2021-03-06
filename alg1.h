/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014

Algorithm 1: Greedy-Immediate Neighbors
Compare all 1-step options (i+1, j+1) (up or right), 
choose LARGEST/SMALLEST (WARNING: STAY IN BOUNDS!), 
ADD to sum, 
RECORD path

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

int alg1(bool min, vector<vector<int> > fData) //Greedy - Immediate Neighbor
{
	int h=fData.size()-1; //looks at the outter most level, giving height
//WARNING: ASSUMES ALL ROWS ARE THE SAME WIDTH
	int w=fData[0].size()-1; //looks at an inner-level, giving width
	int i=0;
	int j=0;
//	string Path = "";
//	string PathReward = "";
	int Reward=fData[0][0]; //We start on this cell, so we pick up its reward
	char choice;

	if (min == true)
	{
		cout << "\nAlg1 MIN on " << h << " x " << w << "... ";
		while (!((i ==h) && (j ==w)))
		{
//			cout << endl << "Current Reward: " << Reward << endl;
//			cout << i << "," << j << ": ";
			if (i+1<= h)
			{
//				cout << "  Inside i+1(" << i+1 << ") <= h(" << h << ")";
				if (j+1<=w)
				{
//					cout << "   Inside j+1(" << j+1 << ") <= w(" << w << ")" <<endl;
					choice = choose(min,fData[i+1][j],fData[i][j+1]); //Up first, Right second
					switch (choice)
					{
					case 'U': 
//						cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go RIGHT." << endl;
//						Path.append("U");
						i++;
						Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
						//PathReward += string version of the int at this location along with a "+"
						break;
					case 'R':
//						cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go UP." << endl;
//						Path.append("R");
						j++;
						Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
						//PathReward += string version of the int at this location along with a "+"
						break;
					default:
						cout << "Hit default statement within MIN switch. CORRUPTED DATA FROM choose() function! \n";
						break;
					} //end switch
				}
				else //if (j+1>w)
				{
//					cout << "j = " << j << " so I'm FORCED to go UP (+"<<fData[i+1][j]<<")" << endl;
//					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					//PathReward += string version of the int at this location along with a "+"
				}
			}
			else //if (i+1>h)
			{
				if (j+1<=w)
				{
//					cout << "i = " << i << " so I'm FORCED to go RIGHT (+"<<fData[i][j+1]<<")" << endl;
//					Path.append("R");
					j++;
					Reward += fData[i][j];
					//PathReward += string version of the int at this location along with a "+"
				}
				else //this should never be reached because j+1>h and i+1>w should break out of the while loop.
				{
					cout << "Hit error statement 1" << endl;
					cout << "i,j = " << i << "," << j << "\nh,w = " << h << "," << w << endl;
					break;
				}
			}
		}
	}
	else //if min == false
	{
		cout << "\nAlg1 MAX on " << h << " x " << w << "... " ;
		while (!((i ==h) && (j ==w)))
		{
//			cout << endl << "Current Reward: " << Reward << endl;
//			cout << i << "," << j << ": ";
			if (i+1<= h)
			{
//				cout << "  Inside i+1(" << i+1 << ") <= h(" << h << ")";
				if (j+1<=w)
				{
//					cout << "   Inside j+1(" << j+1 << ") <= w(" << w << ")" << endl;
					choice = choose(min,fData[i+1][j],fData[i][j+1]); //Up first, Right second
					switch (choice)
					{
					case 'U': 
//						cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go RIGHT." << endl;
//						Path.append("U");
						i++;
						Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at j+1
						//PathReward += string version of the int at this location along with a "+"
						break;
					case 'R':
//						cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go UP." << endl;
//						Path.append("R");
						j++;
						Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at i+1
						//PathReward += string version of the int at this location along with a "+"
						break;
					default:
						cout << "Hit default statement within MAX switch. CORRUPTED DATA FROM choose() function!\n";
						break;
					} //end switch
				}
				else //if (j+1>w)
				{
//					cout << "j = " << j << " so I'm FORCED to go UP (+"<<fData[i+1][j]<<")" << endl;
//					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					//PathReward += string version of the int at this location along with a "+"
				}
			}
			else //if (i+1>h)
			{
				if (j+1<=w)
				{
//					cout << "i = " << i << " so I'm FORCED to go RIGHT (+"<<fData[i][j+1]<<")" << endl;
//					Path.append("R");
					j++;
					Reward += fData[i][j];
					//PathReward += string version of the int at this location along with a "+"
				}
				else //this should never be reached because j+1>h and i+1>w should break out of the while loop.
				{
					cout << "Hit error statement 2" << endl;
					cout << "i,j = " << i << "," << j << "\nh,w = " << h << "," << w << endl;
					break;
				}
			}
		}
	}
	//PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	cout << "...Reward: " << Reward << endl; //"\nPath taken: " << Path << endl;
	return Reward;
}
