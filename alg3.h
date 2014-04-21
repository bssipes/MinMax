/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014

Algorithm 3: Random Choice
While this makes no attempt to be the best, it'll help to make sure I have safeguards in for going out of bounds
Test x times, pretend largest is the "approximate" maximum and the smaller is the "approximate" minimum.

Overall, there are 4 options.
CHOOSE to go RIGHT
CHOOSE to go UP
FORCED to go UP
FORCED to go RIGHT
*/
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

char chooseRandom()
{
	int x=rand()%2;
	if (x==0){return 'U';}
	else {return 'R';}
}

//CODE ADAPTED FROM http://minhazulhaque.blogspot.com/2012/11/sort-vector-of-pairs-based-on-first-or-second-element.html
bool compare (const pair<int,string>&x, const pair<int,string>&y)
{
	return x.first < y.first;
}

pair<int,int> alg3(int runs, vector<vector<int> > fData) //Random
{
	int h=fData.size()-1; //looks at the outter most level, giving height
//WARNING: ASSUMES ALL ROWS ARE THE SAME WIDTH
	int w=fData[0].size()-1; //looks at an inner-level, giving width
	int i;
	int j;
	int k=0;
	string Path;
	string PathReward;
	int Reward; //We start on this cell, so we pick up its reward
	char choice;
	vector<pair<int,string>> solutions;
	{
		cout << "\nAlg3 RANDOM for " << runs << " runs on " << h << " x " << w <<endl;
		while (k<runs) //0 to 99
		{
			//reset variables to initial values
			i=0;
			j=0;
//			Path = "";
//			PathReward = "";
			Reward = fData[0][0];
			
			while (!((i ==h) && (j ==w)))
			{
				if (i+1<= h)
				{
					if (j+1<=w)
					{
						choice = chooseRandom(); //Up first, Right second
						switch (choice)
						{
						case 'U': 
//							Path.append("U");
							i++;
							Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at j+1
							//PathReward += string version of the int at this location along with a "+"
							break;
						case 'R':
//							Path.append("R");
							j++;
							Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at i+1
							//PathReward += string version of the int at this location along with a "+"
							break;
						default:
							cout << "Hit default statement within switch. CORRUPTED DATA FROM chooseRandom() function! \n";
							break;
						} //end switch
					}
					else //if (j+1>w)
					{
//						Path.append("U");
						i++;
						Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at i+1
						//PathReward += string version of the int at this location along with a "+"
					}
				}
				else //if (i+1>h)
				{
					if (j+1<=w)
					{
//						Path.append("R");
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
			} //finish a single path
			solutions.push_back(std::make_pair(Reward,Path));
			k++;
		} //finish the 100 random paths
		sort(solutions.begin(), solutions.end(), compare);
		cout << "The MIN Reward found: " << solutions[0].first << endl;
//		cout << "Path taken: " << solutions[0].second <<endl;
		cout << endl << "The MAX Reward found: " << solutions[solutions.size()-1].first << endl;
//		cout << "Path taken: " << solutions[solutions.size()-1].second <<endl;
	}
	//PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	return (std::make_pair(solutions[0].first, solutions[solutions.size()-1].first));
}
