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
	map<string, int> myMap;

	int index1;		// place holder for string for first node
	int index2;		// place holder for string for second node

	string name1;	// string of first node
	string name2;	// string of second node

	int cost;		// cost between two nodes

	// prompt user for input and obtain first node and second node

	// NODE 1
	// verify if node1 is mapped, if not map it, if is, return index and increment
	cout << "Enter name of the first node: ";
	cin >> name1; 
	cout << endl;

	if ( myMap.find (name1) )
	{
		index1 = myMap._Key (name1);
	}
	else
	{
		myMap.insert (name1);
		nodeCount_ ++;
	}
	
	// NODE 2
	// verify if node2 is mapped, if not map it, if is, return index and increment
	cout << "Enter name of the second node: ";
	cin >> name2;
	cout << endl;
	if ( myMap.find (name2) )
	{
		index2 = myMap._Key (name2);
	}
	else
	{
		myMap.insert (name2);
		nodeCount_ ++;
	}

	// prompt user for cost information between the nodes
	cout << "Enter the cost between the two nodes: ";
	cin >> cost;
	cout << endl;

	// establishing the edge
	Edge_ edge;

	edge.from_ = index1;
	edge.to_ = index2;
	edge.cost_ = cost;

	myMap.insert (edge);
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
	GraphM::T_ = new TableType [nodeCount_];
	GraphM::C_ = new (int *)[nodeCount_];

	for (int iterate = 0; iterate < nodeCount_; iterate ++)
	{
		GraphM::C_ = new int[nodeCount_];
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

bool Network_Cost::insertEdge( )
{

}

/******************************************************************************/
/*	removeEdge (int v, int w)
/*
/*	purpose:	removes an edge from table
/*	pre:		none
/*	post:		
/*
/******************************************************************************/

bool Network_Cost::removeEdge (int v, int w)
{

}

/******************************************************************************/
/*	findShortestPath()
/*
/*	purpose:	Given a cost table, and source & destination find the short path
/*	pre:		none
/*	post:		
/*
/******************************************************************************/

void Network_Cost::findShortestPath()
{

}
