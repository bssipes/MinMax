/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014
Version 0.2

PRE-ALGORITHM SETUP
1) Read in a source file of numbers and GENERATE an 'array' based on this file
(Potentially CSV or seperated by spaces / new lines. Data structure is not set in stone and should be tested for efficiency)
2) Add in code to time the algorithm
(SVC-calls, CPTime)

Algorithm 1: Greedy-Immediate Neighbors
Compare all 1-step options (i+1, j+1) (up or right), choose LARGEST/SMALLEST (WARNING: STAY IN BOUNDS!), ADD to sum, RECORD path

Algorithm 2: Greedy- Min/Max Values of Array
Make a copy of the array and sort it by value
Go directly to the largest value 
(implemented option: travel right until correct column, then up to correct row)
Go to next largest (target[j] >= current[j] and target[i] >= current[i]) by the same option

Algorithm 3: Random Choice
While this makes no attempt to be the best, it'll help to make sure I have safeguards in for going out of bounds
Test x times, pretend largest is the "approximate" maximum and the smaller is the "approximate" minimum.

Algorithm 4: 
Sum all choices by row and by column
For each choice, choose whichever has a smaller sum (to maximize)
or larger sum (minimize)
If they're equal, greedy (choose whichever is higher/lower of the immediate choices)
(NOTE: I will need to constantly update the values for each row and column as I move. Is this worth it?)


Version History: 
0.1: Only comments. Wrote up general algorithms for 1, 2, 3, and 4 and described the problem setup steps
0.2: Able to parse provided sample data
*/

#include <fstream>
#include "alg1.h"
#include "alg2.h"
#include "alg3.h"

vector<vector<int> > readFile(string filename)
{
	vector<vector<int> > inputData;
	vector<int> currentRow;
	ifstream fin(filename);
	string line;
	std::getline(fin,line, ','); //read in the first line until a comma, which is the height
	int height = atoi(line.c_str());
	std::getline(fin,line); //the rest of the first line is the width
	int width = atoi(line.c_str());
	
	for(unsigned k=0;k<height;k++)
	{
		for(unsigned l=0;l<width;l++)
		{
			std::getline(fin,line, ','); //read in x value, discard
			std::getline(fin,line, ','); //read in y value, discard
			std::getline(fin,line); //read in the actual value
			currentRow.push_back(atoi(line.c_str())); //converts the value from str to int
//			cout << l;
		}
		inputData.push_back(currentRow); //places currentRow instead fileData vector
		currentRow.clear();
//		cout << "Finished reading row " << k << endl;
	}
	fin.close();
//	cout << "Finished reading the whole file." << endl;
	return inputData;
}

void main()
{
	vector<vector<int> > fileData = readFile("data.txt");
	alg1(true,fileData);
	alg1(false,fileData);
	alg2(true,fileData);
	alg2(false,fileData);
	alg3(100000, fileData); //100,000 runs
	return;
}
