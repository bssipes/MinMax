/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014
Version 0.7

PRE-ALGORITHM SETUP
1) Read in a source file of numbers and GENERATE an 'array' based on this file
(Potentially CSV or seperated by spaces / new lines. Data structure is not set in stone and should be tested for efficiency)
2) Add in code to time the algorithm

Algorithm 1: Greedy-Immediate Neighbors
Compare all 1-step options (i+1, j+1) (up or right), choose LARGEST/SMALLEST (WARNING: STAY IN BOUNDS!), ADD to sum, RECORD path

Algorithm 2: Greedy- Min/Max Values of Array
Make a copy of the array and sort it by value
Go directly to the largest value 
(implemented option: travel right until correct column, then up to correct row)
Go to next largest (target[j] >= current[j] and target[i] >= current[i]) by the same option

Algorithm 3: Random Choice
While this makes no attempt to be the best, it'll help to make sure I have safeguards in for going out of bounds
Test x times, largest is the "approximate" maximum and the smallest is the "approximate" minimum.

Algorithm 4: Opportunity Costs SUM
Calculate the SUM of the column ABOVE, Calculate the SUM of the row RIGHT
Compare these 2, Choose larger sum if max, Choose lower sum if min

Algorithm 5: Opportunity Costs AVG
Calculate the AVG of the column ABOVE, Calculate the AVG of the row RIGHT
Compare these 2, Choose larger sum if max, Choose lower sum if min

Version History:
0.1: Only comments. Wrote up general algorithms for 1, 2, 3, and 4 and described the problem setup steps
0.2: Able to parse provided sample data
0.3: #includes and calls to Alg1, Alg2, and Alg3 (min/max, min/max, and "x runs" respectively)
0.4: Added WALL and CPU timers to each individual function, as well as the whole program
0.5: Added a function to randomly generate data on any sized input and save the document. The rest of the program
	is unaffected, sparing the name of the file from which I read data.
0.51: Attempted to store, sort, and print master results. Getting conversion error.
"Error	2	error C2664: 'std::basic_string<_Elem,_Traits,_Ax>::basic_string(const std::basic_string<_Elem,_Traits,_Ax> &)' : cannot convert parameter 1 from 'int' to 'const std::basic_string<_Elem,_Traits,_Ax> &'	c:\program files (x86)\microsoft visual studio 10.0\vc\include\utility	163"
0.6: Fixed the conversion error. It was being caused by compare() from alg3, which expected pair<int,string>. Made a new compareII for pair<int,int>
	Cleaned up a lot of the extra cout statements (such as the Path prints). Still in comments.
0.7: Added Alg4 and Alg5
	*/

#include <fstream>
#include "alg2.h"
#include "alg3.h"
#include "alg5.h" //alg5 uses 4 which uses alg1 because of conflicts with choose.h being imported twice. Will try to resolve later.
#include <time.h>

void generateData(int height, int width)
{
	srand (time(NULL));
	ofstream fout;
	fout.open("random.txt");
	fout << height << ", " << width << endl;
	for (int i=1; i<=height;i++)
	{
		for (int j=1; j<=width;j++)
		{
			fout << i << ", " << j << ", " << ((rand()%100)+1) << endl;
		}
	}
	fout.close();
	return;
}

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
	
	for(int k=0;k<height;k++)
	{
		for(int l=0;l<width;l++)
		{
			std::getline(fin,line, ','); //read in x value, discard
			std::getline(fin,line, ','); //read in y value, discard
			std::getline(fin,line); //read in the actual value
			currentRow.push_back(atoi(line.c_str())); //converts the value from str to int
		}
		inputData.push_back(currentRow); //places currentRow instead fileData vector
		currentRow.clear();
	}
	fin.close();
	return inputData;
}

//The following 2 functions are from:  http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows
#ifdef _WIN32
#include <Windows.h>
double get_wall_time()
{
    LARGE_INTEGER time,freq;
    if (!QueryPerformanceFrequency(&freq))
	{
        //  Handle error
        return 0;
    }
    if (!QueryPerformanceCounter(&time))
	{
        //  Handle error
        return 0;
    }
    return (double)time.QuadPart / freq.QuadPart;
}
double get_cpu_time()
{
    FILETIME a,b,c,d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0)
	{
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }
	else
	{
        //  Handle error
        return 0;
    }
}
#endif

bool compareII (const pair<int,int>&x, const pair<int,int>&y)
{
	return x.first < y.first;
}

void main()
{
	//cout << "Generating random data now... ";
	double wall10 = get_wall_time();
	double cpu10 = get_cpu_time();
	//generateData(1024, 1024);
	//double wall12 = get_wall_time();
	//double cpu12 = get_cpu_time();
	//cout << "data generation complete!\n";
	//cout << "Wall Time to generate= " << wall12 - wall10;
 //   cout << "\tCPU Time to generate= " << cpu12  - cpu10  << endl;
	vector<vector<int> > fileData = readFile("random.txt");
//  vector<vector<int> > fileData = readFile("data.txt");
	vector<pair<int,int> > minResults;
	vector<pair<int,int> > maxResults;

//Alg1 MIN
	double wall0 = get_wall_time();
	double cpu0 = get_cpu_time();
	int alg1min = alg1(true,fileData);
	minResults.push_back(std::make_pair(alg1min, 1));
	double wall1 = get_wall_time();
	double cpu1 = get_cpu_time();
	cout << "Wall Time = " << wall1 - wall0;
    cout << "\tCPU Time  = " << cpu1  - cpu0  << endl;

//Alg1 MAX
	double wall2 = get_wall_time();
	double cpu2 = get_cpu_time();
	int alg1max = alg1(false,fileData);
	maxResults.push_back(std::make_pair(alg1max, 1));
	double wall3 = get_wall_time();
	double cpu3 = get_cpu_time();
	cout << "Wall Time = " << wall3 - wall2;
    cout << "\tCPU Time  = " << cpu3  - cpu2  << endl;

//Alg2 MIN
	double wall4 = get_wall_time();
	double cpu4 = get_cpu_time();
	int alg2min = alg2(true,fileData);
	minResults.push_back(std::make_pair(alg2min, 2));
	double wall5 = get_wall_time();
	double cpu5 = get_cpu_time();
	cout << "Wall Time = " << wall5 - wall4;
    cout << "\tCPU Time  = " << cpu5  - cpu4  << endl;

//Alg2 MAX
	double wall6 = get_wall_time();
	double cpu6 = get_cpu_time();
	int alg2max = alg2(false,fileData);
	maxResults.push_back(std::make_pair(alg2max, 2));
	double wall7 = get_wall_time();
	double cpu7 = get_cpu_time();
	cout << "Wall Time = " << wall7 - wall6;
    cout << "\tCPU Time  = " << cpu7  - cpu6  << endl;

//Alg3 10,000 runs
	double wall8 = get_wall_time();
	double cpu8 = get_cpu_time();
	pair<int,int> alg3results = alg3(10000, fileData); //10,000 runs
	minResults.push_back(std::make_pair(alg3results.first, 3));
	maxResults.push_back(std::make_pair(alg3results.second, 3));
	double wall9 = get_wall_time();
	double cpu9 = get_cpu_time();
	cout << "Wall Time = " << wall9 - wall8;
    cout << "\tCPU Time  = " << cpu9  - cpu8  << endl;

//Alg4 MIN
	double wall13 = get_wall_time();
	double cpu13 = get_cpu_time();
	int alg4min = alg4(true,fileData);
	minResults.push_back(std::make_pair(alg4min, 4));
	double wall14 = get_wall_time();
	double cpu14 = get_cpu_time();
	cout << "Wall Time = " << wall14 - wall13;
    cout << "\tCPU Time  = " << cpu14  - cpu13  << endl;

//Alg4 MAX
	double wall15 = get_wall_time();
	double cpu15 = get_cpu_time();
	int alg4max = alg4(false,fileData);
	minResults.push_back(std::make_pair(alg4max, 4));
	double wall16 = get_wall_time();
	double cpu16 = get_cpu_time();
	cout << "Wall Time = " << wall16 - wall15;
    cout << "\tCPU Time  = " << cpu16  - cpu15  << endl;

//Alg5 MIN
	double wall17 = get_wall_time();
	double cpu17 = get_cpu_time();
	int alg5min = alg5(true,fileData);
	minResults.push_back(std::make_pair(alg5min, 5));
	double wall18 = get_wall_time();
	double cpu18 = get_cpu_time();
	cout << "Wall Time = " << wall18 - wall17;
    cout << "\tCPU Time  = " << cpu18  - cpu17  << endl;

//Alg5 MAX
	double wall19 = get_wall_time();
	double cpu19 = get_cpu_time();
	int alg5max = alg5(false,fileData);
	minResults.push_back(std::make_pair(alg5max, 5));
	double wall20 = get_wall_time();
	double cpu20 = get_cpu_time();
	cout << "Wall Time = " << wall20 - wall19;
    cout << "\tCPU Time  = " << cpu20  - cpu19  << endl;

//Compare Results (compare is in MAIN, because alg3 is for pair<int,string> not pair<int,int>)
	sort(minResults.begin(), minResults.end(), compareII);
	sort(maxResults.begin(), maxResults.end(), compareII);
	cout << endl << "The overall smallest reward (" << minResults[0].first << ") was found by Alg" << minResults[0].second << endl;
	cout << "The overall largest reward (" << maxResults[maxResults.size()-1].first << ") was found by Alg" << maxResults[maxResults.size()-1].second << endl;
//Print final time results
	double wall11 = get_wall_time();
	double cpu11 = get_cpu_time();
	cout << endl << "Entire Program Wall Time = " << wall11 - wall10;
    cout << "\tEntire Program CPU Time  = " << cpu11  - cpu10  << endl;

	return;
}
