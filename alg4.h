/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014

Algorithm 4: Opportunity Costs
Calculate the SUM of the column ABOVE
Calculate the SUM of the row RIGHT
Compare these 2
Choose larger sum if max
Choose lower sum if min

Overall, there are 4 options.
CHOOSE to go RIGHT
CHOOSE to go UP
FORCED to go UP
FORCED to go RIGHT
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm> //for std::sort
#include "alg1.h"
using namespace std;

int alg4(bool min, vector<vector<int> > fData) //Opportunity Costs
{
	int h=fData.size()-1; //looks at the outter most level, giving height
//WARNING: ASSUMES ALL ROWS ARE THE SAME WIDTH
	int w=fData[0].size()-1; //looks at an inner-level, giving width
	int i=0; //iterator for height
	int j=0; //iterator for width
//	string Path = "";
	int Reward=fData[0][0]; //We start on this cell, so we pick up its reward
	char choice;
	int columnSUM=0;
	int rowSUM=0;

	if (min == true)
	{
		cout << "\nAlg4 MIN on " << h << " x " << w << "... ";
	}
	else
	{
		cout << "\nAlg4 MAX on " << h << " x " << w << "... ";
	}
	while (!((i ==h) && (j ==w)))
	{
		//TEST if we can increase height
		if (i+1<= h)
		{
			//TEST if we can increase width
			if (j+1<=w)
			{
				//Calculate the SUM of the column ABOVE
				columnSUM=0; //reset to initial value before += occurs
				for (int k=i+1;k<=h;k++)
				{
					columnSUM+= fData[k][j];
				}

				//Calculate the SUM of the row RIGHT
				rowSUM=0;
				for (int m=j+1;m<=h;m++)
				{
					rowSUM+= fData[i][m];
				}

				//Compare these 2 and choose the min 
				choice = choose(min,columnSUM,rowSUM); //Up first, Right second
				switch (choice) //// if R is less than or equal, choose R
				{
				case 'U': 
					i++;
					Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at j+1
					break;
				case 'R':
					j++;
					Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
					break;
				default:
					cout << "Hit default statement within MIN switch. CORRUPTED DATA FROM choose() function! \n";
					break;
				} //end switch
			}
			else //if (j+1>w)
			{
				i++;
				Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
			}
		}
		else //if (i+1>h)
		{
			if (j+1<=w)
			{
				j++;
				Reward += fData[i][j];
			}
			else //this should never be reached because j+1>h and i+1>w should break out of the while loop.
			{
				cout << "Hit error statement 1" << endl;
				cout << "i,j = " << i << "," << j << "\nh,w = " << h << "," << w << endl;
				break;
			}
		}
	} //end while statement
	cout << "...Reward: " << Reward << endl;
	return Reward;
}
