/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014

Algorithm 2: Greedy- Min/Max Values of Array
Make a copy of the array and sort it by value
Go directly to the largest value 
(implemented option: travel right until correct column, then up to correct row)
Go to next largest (target[j] >= current[j] and target[i] >= current[i]) by the same option

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
using namespace std;

	class cV //Coordinate Pair + Value
	{
	private:
		int height, width, value;
	public:
		int getH(){return height;}
		int getW(){return width;}
		int getValue(){return value;}
		cV(int h, int w, int v){height = h; width = w; value = v;};
		bool operator < (const cV &other) const
		{
			//Sorts by Value, then W, then H (smallest to largest)
			if (value != other.value) return value < other.value;
			else if (width != other.width) return width < other.width;
			else return height < other.height;
		}
		bool operator > (const cV &other) const
		{
			//Sorts by Value, then W, then H (largest to smallest)
			if (value != other.value) return value > other.value;
			else if (width != other.width) return width > other.width;
			else return height > other.height;
		}
	}; //end class cV

int alg2(bool min, vector<vector<int> > fData) //Greedy - Min/Max of entire grid
{
	int h=fData.size()-1; //looks at the outter most level, giving height
//WARNING: ASSUMES ALL ROWS ARE THE SAME WIDTH
	int w=fData[0].size()-1; //looks at an inner-level, giving width
	int i=0; //iterator for height
	int j=0; //iterator for width
	int k=0; //iterator for sortedData
//	string Path = "";
//	string PathReward = "";
	int Reward=fData[0][0]; //We start on this cell, so we pick up its reward
//	bool movedRight = false;
//	bool movedUp = false;

	vector<cV> sortedData;
	for (i=0; i<=h; i++)
	{
		j=0;
		for (j=0; j<=w; j++)
		{
			if (i==0 && j==0)
			{
				j++;
			}
			sortedData.push_back(cV(i,j,fData[i][j])); //// PLACES ALL VALUES INTO A 1D VECTOR
		}
	} //end stripping 2d into 1d vector
	i=0;
	j=0;
	if (min == true)
	{
		cout << "\nAlg2 MIN on " << h << " x " << w << "... ";
		std::sort(sortedData.begin(), sortedData.end()); //SORTED FROM SMALLEST TO LARGEST BY: VALUE, WIDTH, HEIGHT
	}
	else //min == false
	{
		cout << "\nAlg2 MAX on " << h << " x " << w << "... ";
		//sort(sortedData.rbegin(), sortedData.rend()); //SORTED FROM LARGEST TO SMALLEST (reverse iterators) BY: VALUE, WIDTH, HEIGHT
		std::reverse(sortedData.begin(), sortedData.end());
		
	}
	while (!((i ==h) && (j ==w)))
	{
		if (sortedData[k].getW()>=j && sortedData[k].getH()>=i)
		{
			while (j<sortedData[k].getW())
			{
//				movedRight = true;
//				cout << "RIGHT from " << i << "," << j << " to " << i << "," << j+1 << " and picking up (" << fData[i][j] <<") with destination: " << sortedData[k].getH() << "," << sortedData[k].getW() << endl;
//				Path.append("R");
				j++;
				Reward += fData[i][j]; //j was increased before the summation, no need to look ahead at j+1
				//PathReward += string version of the int at this location along with a "+"
			}
//			if (movedRight)
//			{
//				cout << "Arrived at " << i << "," << j << " to pick up value: " << fData[i][j] <<endl;
//			}
			while (i<sortedData[k].getH())
			{
//				movedUp = true;
//				cout << "UP from " << i << "," << j << " to " << i+1 << "," << j << " and picking up (" << fData[i][j] <<") with destination: " << sortedData[k].getH() << "," << sortedData[k].getW() << endl;
//				Path.append("U");
				i++;
				Reward += fData[i][j]; //i was increased before the summation, no need to look ahead at j+1
				//PathReward += string version of the int at this location along with a "+"
			}
//			if (movedUp) 
//			{
//				cout << "Arrived at " << i << "," << j << " to pick up value: " << fData[i][j] <<endl;
//			} // don't want to display this message twice if we didn't actually move
//			movedRight = false;
//			movedUp = false;
//			cout << "k = " << k << " has been achieved. Incrementing to " << k+1 << endl;
			k++;//after finishing both of these while loops, we've arrived at the value (sortedData[k]) we were after
//			cout << "k = " << k << endl;
		}
		else
		{
			//if the coordinate of the cV is to the left of where we already are, it is unreachable.
			//likewise, anything below where we already are is unreachable.
			//thusly, it needs to be skipped.
//			cout << "k = " << k << " is being skipped." << endl;
			k++;
		}
	}
	//PathReward.erase(PathReward.length()-1); //remove the trailing + before printing
	cout << "...Reward: " << Reward << endl; //"\nPath taken: " << Path << endl;
	return Reward;
}
