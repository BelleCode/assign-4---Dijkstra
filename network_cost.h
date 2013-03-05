//	****************************************************************************
//	network_cost.h
//
//	Project: lab04
// 	purpose: 
//		read a cost table from cin and take two command line arguments for the 
//		start and end cities
//	goal:
//		Computes the minimum-cost path and print to cout in proper order in the
//		same format
//	
//
//	****************************************************************************

#ifndef NETWORK_COST_H
#define NETWORK_COST_H

#include <iostream>
#include <string>			// for string manipulation
#include <list>				// for use of building a list of edges
#include <map>				// storing the information in easy to find way

class Network_Cost
{
public:
	Network_Cost();							// Constructor

	void readInput(std::string from, std::string to);	// reads in input from command line
	void outputShortestPath();				// produces output
	
private:

	int nodeCount_;					// keeps track of the count of nodes to 
									// allow for the establishing of size of 
									// cost tables
	
	int source_;
	int dest_;

	struct TableType
	{
		bool visited_;				// whether node has been visited
		int dist_;					// shortest distance from source known so far
		int path_;					// previous node in path of min dist
	};

	TableType *T_;					// pointer to a TableType object
	int **C_;						// pointer to a pointer to a Cost Matrix 
		
	std::map <std::string, int> nodeMap;			// maps node names to indexes returns int	
	std::map <int, std::string> reverseNodeMap;	// reverses map of node names
	
	struct Edge_
	{
		int from_;					// 'v' or source
		int to_;					// 'w' or destination
		int cost_;					// what it costs to go from v -> w
	};

	std::list <Edge_> edgeList;			// list

	void _insertEdge();				// inserts the edges
	bool _readInputHelper();
	void _initializeTables();		// fill table with infinity
	void _allocateTables();			// allocates the right sizes
	void _findShortestPath();		// shortest path
};
#endif