//	****************************************************************************
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
//	****************************************************************************

#include "network_cost.h"

#include <iostream>
#include <string>			// for string manipulation
#include <list>				// for use of building a list of edges
#include <map>				// storing the information in easy to find way

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
//	Public Functions
//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*	CONSTRUCTOR
/*
/*	purpose:	creates a linked list graph
/*	pre:		none
/*	post:		size of the item is established
/*
/******************************************************************************/
Network_Cost::Network_Cost()
{

}

/******************************************************************************/
/*	readInput
/*
/*	purpose:	prompts user for information, 1st node & 2nd node, they can be
/*				the same, or different, then prompts user for cost
/*	pre:		none
/*	post:		size of the item is established
/*
/******************************************************************************/

void Network_Cost::readInput()
{
	int index1;		// place holder for string for first node
	int index2;		// place holder for string for second node

	string name1;	// string of first node
	string name2;	// string of second node

	// prompt user for input and obtain first node and second node
	cout << "Enter name of the first node: ";
	cin >> name1; 
	cout << endl;
	cout << "Enter name of the second node: ";
	cin >> name2 
	cout << endl;


	map <string, int> Dijkstra;

	if ( map <name1>)
}	

/******************************************************************************/
/*	allocate
/*
/*	purpose:	allocates the right sizes for t
/*	pre:		none
/*	post:		size of the item is established
/*
/******************************************************************************/

void Network_Cost::allocate ()
{
	T_ = new TableType [nodeCount_];
	C_ = new (int *)[nodeCount_];

	for (int iterate = 0; iterate < nodeCount_; iterate ++)
	{
		C_ = new int[nodeCount_];
	}
}

/******************************************************************************/
/*	insertEdge
/*
/*	purpose:	inserts edge information 
/*	pre:		none
/*	post:		size of the item is established
/*
/******************************************************************************/

bool Network_Cost::insertEdge( Network_Cost::EDGE_);	// inserts the edges
	bool Network_Cost::removeEdge (int v, int w);			// removes Edge from table
	void Network_Cost::findShortestPath();				// shortest path

	void Network_Cost::allocate ();			// allocates the right sizes for t


