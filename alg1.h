#include <string>
#include <iostream>
#include <vector>
using namespace std;
/*
Overall, there are 4 options.
CHOOSE to go RIGHT
CHOOSE to go UP
FORCED to go UP
FORCED to go RIGHT
*/
char choose(bool min, int R, int U)
{
	char result;
	if (min == true)
	{
		if (U < R)
		{
			result = 'U';
		}
		else // if R is less than or equal, choose R
		{
			result = 'R';
		}
	}
	else if (min == false)
	{
		if (U > R)
		{
			result = 'U';
		}
		else //if R is larger or equal, choose R
		{
			result = 'R';
		}
	}
	return result;
}

void alg1(bool min, vector<vector<int> > fData) //Greedy - Immediate Neighbor
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
		cout << "\nAlg1 MIN on " << h << " x " << w <<endl;
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
					choice = choose(min,fData[i+1][j],fData[i][j+1]); //Right first, Up second
					switch (choice)
					{
					case 'U': 
//						cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go RIGHT." << endl;
						Path.append("R");
						j++;
						Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
						PathReward += fData[i][j];
						PathReward += " +";
						break;
					case 'R':
//						cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go UP." << endl;
						Path.append("U");
						i++;
						Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
						PathReward += fData[i][j];
						PathReward += " +";
						break;
					default:
						cout << "Hit default statement within MIN switch. ERROR\n";
						break;
					} //end switch
				}
				else //if (j+1>w)
				{
//					cout << "j = " << j << " so I'm FORCED to go UP (+"<<fData[i+1][j]<<")" << endl;
					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j];
					PathReward += " +";
				}
			}
			else if (i+1>h)
			{
				if (j+1<=w)
				{
//					cout << "i = " << i << " so I'm FORCED to go RIGHT (+"<<fData[i][j+1]<<")" << endl;
					Path.append("R");
					j++;
					Reward += fData[i][j];
					PathReward += fData[i][j];
					PathReward += " +";
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
	//else if (min == false)
	else
	{
		cout << "\nAlg1 MAX on " << h << " x " << w <<endl;
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
					choice = choose(min,fData[i+1][j],fData[i][j+1]); //min is the name of the bool, don't panic.
					switch (choice)
					{
					case 'U': 
//						cout << fData[i+1][j] << " < " << fData[i][j+1] << " thus I CHOOSE to go RIGHT." << endl;
						Path.append("R");
						j++;
						Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
						PathReward += fData[i][j];
						PathReward += " +";
						break;
					case 'R':
//						cout << fData[i+1][j] << " > " << fData[i][j+1] << " thus I CHOOSE to go UP." << endl;
						Path.append("U");
						i++;
						Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
						PathReward += fData[i][j];
						PathReward += " +";
						break;
					default:
						cout << "Hit default statement within MAX switch. ERROR\n";
						break;
					} //end switch
				}
				else //if (j+1>w)
				{
//					cout << "j = " << j << " so I'm FORCED to go UP (+"<<fData[i+1][j]<<")" << endl;
					Path.append("U");
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
					PathReward += fData[i][j];
					PathReward += " +";
				}
			}
			else if (i+1>h)
			{
				if (j+1<=w)
				{
//					cout << "i = " << i << " so I'm FORCED to go RIGHT (+"<<fData[i][j+1]<<")" << endl;
					Path.append("R");
					j++;
					Reward += fData[i][j];
					PathReward += fData[i][j];
					PathReward += " +";
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
	PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	cout << endl << "End reached! Reward: " << Reward << "\nPath taken: " << Path << endl;
	return;
}
