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

using namespace std;

class Network_Cost
{
public:
	Network_Cost();							// Constructor

	void readInput();					// reads in input from command line
	void allocate ();					// allocates the right sizes for t
	bool insertEdge();	// inserts the edges
	bool removeEdge (int v, int w);			// removes Edge from table
	void findShortestPath();				// shortest path

private:

	int nodeCount_;				// keeps track of the count of nodes to 
									// allow for the establishing of size of 
									// cost tables

	struct Edge_
	{
		int from_;					// 'v' or source
		int to_;					// 'w' or destination
		int cost_;					// what it costs to go from v -> w
	};

	int v;							// = Edge_.from_;
	int w;							// = Edge_.to_;

	struct TableType
	{
		bool visited_;				// whether node has been visited
		int dist_;					// shortest distance from source known so far
		int path_;					// previous node in path of min dist
	};

	class GraphM
	{
		TableType *T_;				// pointer to a TableType object
		int **C_;				// pointer to a pointer to a Cost Matrix 
	};



};
#endif