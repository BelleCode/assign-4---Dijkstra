//	***************************************************************************
//	main.cpp
//
//	Project: lab04
// 	purpose: 
//		take the output file as input and compute the net cost
//	goal:
//		Computes the minimum-cost path	
//
//	***************************************************************************

#include <iostream>
#include <string>

using namespace std;

bool readAndCompute(string &source, string &destination, int &finalCost);

int main ( )
{

	string source = "";
	string destination = ""; 

	int finalCost = 0;				// final cost

	bool done;

	do
	{ 
		done = !readAndCompute(source, destination, finalCost);
	} while (!done);

	// output final information
	cout << source << "     " << destination << "     " << finalCost << endl;

	return 0;
}

bool readAndCompute(string &source, string &destination, int &finalCost)
{
	string name1 = "";			// string of first node
	string name2 = "";			// string of second node

	int costBtwNodes = 0;		// cost between two nodes

	cin >> name1;				// read in first node
	cin >> name2;				// read in second node
	cin >> costBtwNodes;		// read in cost

	finalCost += costBtwNodes;	// pass sum of cost back out

	// setting up source
	if (source == "")
	{
		if (name1 == "")		// either end of file or blank line
		{
			destination == name2;
			return false;
		}
		source = name1;			// setting up the source
	}
	// if the second one is empty given 1st one is there something wrong, exit
	if (name2 == "")		
	{
		return false;
	}
	destination = name2;		// setting up destination

	return true;
}


