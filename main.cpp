//	***************************************************************************
//	main.cpp
//
//	Project: lab04
// 	purpose: 
//		read a cost table from cin and take two command line arguments for the 
//		start and end cities
//	goal:
//		Computes the minimum-cost path and print to cout in proper order in the
//		same format
//	
//	reference & authors:
//		http://www.cplusplus.com/articles/DEN36Up4/
//
//	***************************************************************************

#include <iostream>
#include <fstream>
#include <string>

#include "network_cost.h"

using namespace std;

int main (int argc, char* argv[])	
{

	// run Dikjstra's
	Network_Cost Dijkstra;
	
	if (argc != 3 && argc != 5)
	{
		cout << "You done bad!!!!! Please enter the correct number of args" 
			 << endl;
		return 1;
	}
	
	string to (argv[2]);
	string from (argv[1]);
	
	if (argc == 5)
	{
		if (argv[3][0] == '-' && (argv[3][1] == 'o' || argv[3][1] == 'O'))
		{
			Dijkstra.setOutputFile(argv[4]);
		}
		else
		{
			cout << "You done bad!!!!! Please enter valid args" << endl;
			return 1;
		}
	}
	
	Dijkstra.readInput (from, to);
	Dijkstra.outputShortestPath();

	return 0;
}

