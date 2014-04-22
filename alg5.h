/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014

Algorithm 5: Opportunity Costs
Calculate the AVG of the column ABOVE
Calculate the AVG of the row RIGHT
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
#include "alg4.h" //alg5 uses 4 which uses alg1 because of conflicts with choose.h being imported twice. Will try to resolve later.
using namespace std;

int alg5(bool min, vector<vector<int> > fData) //Opportunity Costs
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
	int columnCNT=1; //count
	float columnAVG=0;
	int rowSUM=0;
	int rowCNT=1; //count
	float rowAVG=0;

	if (min == true)
	{
		cout << "\nAlg5 MIN on " << h << " x " << w << "... ";
	}
	else
	{
		cout << "\nAlg5 MAX on " << h << " x " << w << "... ";
	}
	while (!((i ==h) && (j ==w)))
	{
		//TEST if we can increase height
		if (i+1<= h)
		{
			//TEST if we can increase width
			if (j+1<=w)
			{
				//Calculate the AVG of the column ABOVE
				columnSUM=0; //reset to initial value before += occurs
				for (int k=i+1; k<=h; k++)
				{
					columnSUM+= fData[k][j];
				}
				columnCNT = (w+1) - i;
				columnAVG = (columnSUM/columnCNT);
//max height - current height +1 = number to divide by to get avg

				//Calculate the AVG of the row RIGHT
				rowSUM=0;
				for (int m=j+1;m<=h;m++)
				{
					rowSUM+= fData[i][m];
				}
				rowCNT = (h+1) - j;
				rowAVG = (rowSUM/rowCNT);
//max width - current width +1 = number to divide by to get avg

				//Compare these 2 and choose based on 'bool min'
				choice = choose(min,columnAVG,rowAVG); //Up first, Right second
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
