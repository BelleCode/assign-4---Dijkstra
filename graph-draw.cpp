// graph-draw.cc
//
// Copyright 2013 Systems Deployment, LLC
// Author: Morris Bernstein (morris@systems-deployment.com)

#include "graph-draw.h"

#include <iostream>


using namespace std;


const char* GraphDraw::UNHIGHLIGHT = "NONE";


int GraphDraw::emit(ostream& out) {
  out << "digraph {" << endl;

  for (map<string, Vertex*>::iterator vertex_it = vertices_.begin(); vertex_it != vertices_.end(); ++vertex_it) {
	out << "   " << vertex_it->first << "[label=\"" << vertex_it->first;
	const string& label = vertex_it->second->label();
	if (label != "") {
	  out << "\\n" << label;
	}
	out << "\"";
	if (vertex_it->second->color() != UNHIGHLIGHT) {
	  out << ", style=filled, fillcolor=\"" << vertex_it->second->color() << "\"";
	}
	out << "];" << endl;
  }

  for (map<const VertexPair, Edge*>::iterator edge_it = edges_.begin(); edge_it != edges_.end(); ++edge_it) {
	Edge* edge = edge_it->second;
	out << "   " << edge->from() << " -> " << edge->to() << " [label=\"" << edge->label() << "\"";
	if (edge_it->second->color() != UNHIGHLIGHT) {
	  out << ", color=\"" << edge->color() << "\"";
	}
	out << "];" << endl;
  }

  out << "}" << endl;

  return 0;
}


void GraphDraw::add_node(const string& id) {
  map<string, Vertex*>::iterator it = vertices_.find(id);
  if (it != vertices_.end()) {
	cerr << "GraphDraw::add_node: adding " << id << " already present" << endl;
	return;
  }
  vertices_[id] = new Vertex(id);
}


void GraphDraw::add_edge(const string& v1, const string& v2, const string& label) {
  map<const string, Vertex*>::iterator v1_it = vertices_.find(v1);
  if (v1_it == vertices_.end()) {
	cerr << "adding edge (" << v1 << ", " << v1 << "): " << v1 << " not found" << endl;
	return;
  }
  map<const string, Vertex*>::iterator v2_it = vertices_.find(v2);
  if (v2_it == vertices_.end()) {
	cerr << "adding edge (" << v2 << ", " << v2 << "): " << v2 << " not found" << endl;
	return;
  }
  VertexPair key = VertexPair(*(v1_it->second), *(v2_it->second));
  map<const VertexPair, Edge*>::iterator edge_it = edges_.find(key);
  if (edge_it != edges_.end()) {
	cerr << "adding edge (" << v2 << ", " << v2 << "): edge already present" << endl;
  }
  edges_[key] = new Edge(v1, v2, label);
}


void GraphDraw::unhighlight_nodes() {
  for (map<const string, Vertex*>::iterator it = vertices_.begin(); it != vertices_.end(); ++it) {
	it->second->set_color(UNHIGHLIGHT);
  }
}


void GraphDraw::unhighlight_edges() {
  for (map<const VertexPair, Edge*>::iterator it = edges_.begin(); it != edges_.end(); ++it) {
	it->second->set_color(UNHIGHLIGHT);
  }
}


void GraphDraw::relabel_node(const string& id, const string& label) {
  map<const std::string, Vertex*>::iterator it = vertices_.find(id);
  if (it == vertices_.end()) {
	cerr << "attempting to relabel unknown node " << id << endl;
	return;
  }
  it->second->set_label(label);
}


void GraphDraw::highlight_node(const string& id, const string& color) {
  map<const string, Vertex*>::iterator it = vertices_.find(id);
  if (it == vertices_.end()) {
	cerr << "highlighting nonexistent node: " << id << endl;
	return;
  }
  it->second->set_color(color);
}


void GraphDraw::unhighlight_node(const string& id) {
  highlight_node(id, UNHIGHLIGHT);
}


void GraphDraw::highlight_edge(const string& label1, const string& label2, const string& color) {
  map<const VertexPair, Edge*>::iterator it = edges_.find(VertexPair(Vertex(label1), Vertex(label2)));
  if (it == edges_.end()) {
	cerr << "highlighting nonexistent edge: (" << label1 << ", " << label2 << ")" << endl;
	return;
  }
  it->second->set_color(color);
}


void GraphDraw::unhighlight_edge(const string& label1, const string& label2) {
  highlight_edge(label1, label2, UNHIGHLIGHT);
}


bool operator<(const GraphDraw::VertexPair& edge1, const GraphDraw::VertexPair& edge2) {
  if (edge1.first.id_ < edge2.first.id_) {
	return true;
  } else if ((edge1.first.id_ == edge2.first.id_) &&
		 (edge1.second.id_ < edge2.second.id_)) {
	return true;
  } else {
	return false;
  }
}