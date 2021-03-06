//	***************************************************************************
//	network_cost.cpp
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
//	***************************************************************************

#include "network_cost.h"
#include "graph-draw.h"

#include <iostream>
#include <string>			// for string manipulation
#include <list>				// for use of building a list of edges
#include <map>				// storing the information in easy to find way
#include <math.h>			// to allow for infinity
#include <climits>			// to allow for infinity in linux
#include <sstream>			
#include <iomanip>

#define INFINITE INT_MAX

using namespace std;

// v == From/source
// w == To/ destination

///////////////////////////////////////////////////////////////////////////////
//
//	Public Functions
//
///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/*	CONSTRUCTOR
/*
/*	purpose:	creates a linked list graph
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
Network_Cost::Network_Cost()
{
	nodeCount_ = 0;
	outputFileName_ = "";
}

/*****************************************************************************/
/*	setOutputFile (const string &outputFileName)
/*
/*	purpose:	creates a linked list graph
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
void Network_Cost::setOutputFile (const string &outputFileName)
{
	outputFileName_ = outputFileName;
}

/*****************************************************************************/
/*	readInput
/*
/*	purpose:	Calls readInputHelper to gather information
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
void Network_Cost::readInput(string source, string dest)
{
	bool done;
	// loops run while the readInputHelper is reading valid info
	do
	{
		done = !_readInputHelper();
	}while (!done);

	source_ = nodeMap[source];
	dest_ = nodeMap[dest];

	_allocateTables();
	_initializeTables();
	_insertEdge();

	// make copy of source 
	for (int iterate = 0; iterate < nodeCount_; iterate ++)
	{
		T_[iterate].dist_ =  C_[source_][iterate];

		if (T_[iterate].dist_ != INFINITE)
		{
			T_[iterate].path_ = source_;
		}
	}
	_findShortestPath();
}

/*****************************************************************************/
/*	outputShortestPath
/*
/*	purpose:	Calls readInputHelper to gather information
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
void Network_Cost::outputShortestPath()
{
	// a list of edges in the order they travelled
	list <Edge_> inOrderList;

	Edge_ edge;

	int destination = dest_;
	while (destination != source_)
	{
		edge.from_ = T_[destination].path_;
		edge.to_ = destination;
	
		// calculate edges
		if (edge.from_ != source_)
		{
			edge.cost_ = T_[destination].dist_ - T_[edge.from_].dist_;
		}
		else
		{
			edge.cost_ = T_[destination].dist_;
		}
		// go to next previous node
		destination = T_[destination].path_;
		inOrderList.push_front(edge);
	}

	// iterate over the edgeList insert edge at proper position
	for (list<Edge_>::iterator it = inOrderList.begin(); 
		 it != inOrderList.end(); it++)
	{
		cout << reverseNodeMap[it->from_] << "\t" << reverseNodeMap[it->to_] 
			 << "\t" << it->cost_ << endl; 
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//	Private Functions
//
///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
/*	_readInputHelper
/*
/*	purpose:	prompts user for information, 1st node & 2nd node, they can be
/*				the same, or different, then prompts user for cost
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
bool Network_Cost::_readInputHelper()
{

	int index1;		// place holder for string for first node
	int index2;		// place holder for string for second node

	string name1;	// string of first node
	string name2;	// string of second node

	int cost;		// cost between two nodes

	// prompt user for input and obtain first node and second node

	// NODE 1
	// verify if node1 is mapped, if not map it, if is, 
	// return index and increment
	cin >> name1; 
	if (name1 == "")
	{
		return false;
	}

	// count will return a 1 if found.
	if ( nodeMap.count (name1) == 1)
	{
		// looks up information using operator[]
		index1 = nodeMap[name1];
	}
	else
	{
		index1 = nodeCount_;
		nodeMap[name1] = nodeCount_;
		reverseNodeMap.push_back (name1);
		nodeCount_ ++;
	}
	
	// NODE 2
	// verify if node2 is mapped, if not map it, if is, 
	// return index and increment
	cin >> name2;

	// count will return a 1 if found.
	if ( nodeMap.count (name2) == 1)
	{
		// looks up information using operator[]
		index2 = nodeMap[name2];
	}
	else
	{
		index2 = nodeCount_;
		nodeMap[name2] = nodeCount_;
		reverseNodeMap.push_back (name2);
		nodeCount_ ++;
	}

	// prompt user for cost information between the nodes
	cin >> cost;

	// establishing the edge
	Edge_ edge;

	edge.from_ = index1;
	edge.to_ = index2;
	edge.cost_ = cost;

	// adds the new edge item at the end of the list container
	edgeList.push_back(edge);

	return true;
}	

/*****************************************************************************/
/*	_allocateTables ()
/*
/*	purpose:	allocates the right sizes for t
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
void Network_Cost::_allocateTables ()
{
	// allocates Tabletype object
	T_ = new TableType [nodeCount_];

	// allocates the vertical array
	C_ = new int*[nodeCount_];

	for (int iterate = 0; iterate < nodeCount_; iterate ++)
	{
		// allocates edge costs
		C_[iterate] = new int[nodeCount_];
	}
}

/*****************************************************************************/
/*	_initializeTables();
/*
/*	purpose:	initial all cells in the table to INFINITY 
/*	pre:		none
/*	post:		all cells INFINITY
/*
/*****************************************************************************/
void Network_Cost::_initializeTables()
{
	for (int v = 0; v < nodeCount_; v++)
	{
		// T_ is one dimension 
		// set the weight/cost to 0
		T_ [v].path_ = 0; 

		// set the dist to inifinite unless it's the node we're looking at
		T_ [v].dist_ = INFINITE;		// don't know source initialize all
		T_ [v].visited_ = false;		// node is visited

		for (int w = 0; w < nodeCount_; w++)
		{
			C_ [v][w] = INFINITE;		// adjacency matrix set to infinate
		}
	}
}

/*****************************************************************************/
/*	_insertEdge()
/*
/*	purpose:	inserts edge information 
/*	pre:		none
/*	post:		size of the item is established
/*
/*****************************************************************************/
void Network_Cost::_insertEdge()
{
	// iterate over the edgeList insert edge at proper position
	for (list<Edge_>::iterator it = edgeList.begin(); it != edgeList.end(); it++)
	{
		C_ [it->from_][it->to_] = it->cost_;
	}
}

/*****************************************************************************/
/*	_findShortestPath( )
/*
/*	purpose:	Given cost table, and source & destination find the short path
/*	pre:		none
/*	post:		
/*
/*****************************************************************************/
void Network_Cost::_findShortestPath( )
{
	// implementation of Dijkstra's algorithm
	int v;
	int fileNum = 0;

	// build the GraphDraw object
	GraphDraw gd;

	if (outputFileName_ != "")
	{
		// Add the nodes
		for (unsigned int n = 0; n < reverseNodeMap.size(); n++)
		{
			gd.add_node(reverseNodeMap[n]);
		}

		// add the edges
		for (list<Edge_>::iterator it = edgeList.begin(); 
			 it != edgeList.end(); it++)
		{
			stringstream ss;
			ss << it ->cost_;
			gd.add_edge(reverseNodeMap[it->from_], reverseNodeMap[it-> to_] 
												 , ss.str() ); 
		}
	}

	// start interations of Dijkstra's algorithm
	do
	{
		// find the next v (lowest cost node)
		// set v to an invalid node so we know we can find no more unvisited
		// connections.
		int smallestDist = INFINITE;
		 v = -1;

		// find the closest known, unprocessed node to the sourceNode
		for (int node = 0; node < nodeCount_; node++)
		{
			if ((T_[node].dist_ < smallestDist ) && (!T_[node].visited_) )
			{
				smallestDist = T_[node].dist_;
				v = node;
			}
		}

		if (v != -1)
		{
			// goes through nodes that are connected to v
			// w = destinationNode
			for (int w = 0; w < nodeCount_; w++)
			{
				// verifies that the nodes are connected (!= infinity)
				if ( C_[v][w] != INFINITE)
				{
					// Calculate the distance from Source_ to w using the 
					// distance from Source_ to v and the distance from v to w
					int dist = T_[v].dist_ + C_[v][w];

					// If the new distance from source_ to w is shorter than
					// the existing distance from source_ to w then update
					// T_ with new values
					if (dist < T_[w].dist_)
					{
						T_[w].dist_ = dist;
						T_[w].path_ = v;
					}
				}
			}
			// Processing completed, mark visited as true
			T_[v].visited_=true;
		}

		if (outputFileName_ != "")
		{
			// highlighting the shortest path
			gd.unhighlight();

			int dest = dest_;

			while (dest != source_ && dest != -1)
			{
				string dest_name = reverseNodeMap[dest];
				gd.highlight_node(dest_name, "red");

				int source = T_[dest].path_;

				if (source != -1)
				{
					string source_name = reverseNodeMap[source];
					gd.highlight_node(source_name, "red");

					gd.highlight_edge(source_name, dest_name, "red");
				}

				// go to the next previous node
				dest = T_[dest].path_;
			}

			// output the file
			stringstream fileNameStream;
			
			fileNameStream << outputFileName_ << "-" << setw (4) 
						   << setfill ('0') << fileNum << ".dot";
			fileNum++;

			ofstream outfile (fileNameStream.str().c_str());
			gd.emit(outfile);
		}
	} while (v != -1);
}
