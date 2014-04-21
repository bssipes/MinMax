/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014
Version 0.5

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

Version History: 
0.1: Only comments. Wrote up general algorithms for 1, 2, 3, and 4 and described the problem setup steps
0.2: Able to parse provided sample data
0.3: #includes and calls to Alg1, Alg2, and Alg3 (min/max, min/max, and "x runs" respectively)
0.4: Added WALL and CPU timers to each individual function, as well as the whole program
0.5: Added a function to randomly generate data on any sized input and save the document. The rest of the program
	is unaffected, sparing the name of the file from which I read data.*/

#include <fstream>
#include "alg1.h"
#include "alg2.h"
#include "alg3.h"
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
	
	for(unsigned k=0;k<height;k++)
	{
		for(unsigned l=0;l<width;l++)
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

void main()
{
	double wall10 = get_wall_time();
	double cpu10 = get_cpu_time();
	generateData(100,100);
	vector<vector<int> > fileData = readFile("random.txt");
//  vector<vector<int> > fileData = readFile("data.txt");

//Alg1 MIN
	double wall0 = get_wall_time();
	double cpu0 = get_cpu_time();
	alg1(true,fileData);
	double wall1 = get_wall_time();
	double cpu1 = get_cpu_time();
	cout << "Wall Time = " << wall1 - wall0 << endl;
    cout << "CPU Time  = " << cpu1  - cpu0  << endl;

//Alg1 MAX
	double wall2 = get_wall_time();
	double cpu2 = get_cpu_time();
	alg1(false,fileData);
	double wall3 = get_wall_time();
	double cpu3 = get_cpu_time();
	cout << "Wall Time = " << wall3 - wall2 << endl;
    cout << "CPU Time  = " << cpu3  - cpu2  << endl;

//Alg2 MIN
	double wall4 = get_wall_time();
	double cpu4 = get_cpu_time();
	alg2(true,fileData);
	double wall5 = get_wall_time();
	double cpu5 = get_cpu_time();
	cout << "Wall Time = " << wall5 - wall4 << endl;
    cout << "CPU Time  = " << cpu5  - cpu4  << endl;

//Alg2 MAX
	double wall6 = get_wall_time();
	double cpu6 = get_cpu_time();
	alg2(false,fileData);
	double wall7 = get_wall_time();
	double cpu7 = get_cpu_time();
	cout << "Wall Time = " << wall7 - wall6 << endl;
    cout << "CPU Time  = " << cpu7  - cpu6  << endl;

//Alg3 100,000 runs
	double wall8 = get_wall_time();
	double cpu8 = get_cpu_time();
	alg3(100000, fileData); //100,000 runs
	double wall9 = get_wall_time();
	double cpu9 = get_cpu_time();
	cout << "Wall Time = " << wall9 - wall8 << endl;
    cout << "CPU Time  = " << cpu9  - cpu8  << endl;

	double wall11 = get_wall_time();
	double cpu11 = get_cpu_time();
	cout << endl << "Entire Program Wall Time = " << wall11 - wall10 << endl;
    cout << "Entire Program CPU Time  = " << cpu11  - cpu10  << endl;

	return;
}
