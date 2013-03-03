// graph-draw.h
//
// Generates a dot file (http://www.graphviz.org) representation of a
// graph.
//
// Usage: create an object of class GraphDraw and add content via
// add_node() and add_edge() methods.  Nodes/edges my be highlighted.
// Nodes are identified by a string id and edges are identified by by
// the from/to id pair.
//
// Copyright 2013 Systems Deployment, LLC
// Author: Morris Bernstein (morris@systems-deployment.com)


#if !defined(GRAPH_DRAW_H)
#define GRAPH_DRAW_H


#include <map>
#include <fstream>
#include <string>
#include <utility>


class GraphDraw {
 public:
  explicit GraphDraw() {}
  ~GraphDraw() {}

  int emit(std::ostream& out);

  void add_node(const std::string& id);
  void add_edge(const std::string& v1, const std::string& v2, const std::string& label);

  void unhighlight() {unhighlight_nodes(); unhighlight_edges();}
  void unhighlight_nodes();
  void unhighlight_edges();

  void relabel_node(const std::string& id, const std::string& label);

  void highlight_node(const std::string& id, const std::string& color);
  void unhighlight_node(const std::string& id);

  void highlight_edge(const std::string& from, const std::string& to, const std::string& color);
  void unhighlight_edge(const std::string& from, const std::string& to);

  class Vertex;
  typedef std::pair<Vertex, Vertex> VertexPair;

  class Vertex {
  public:
    Vertex(const std::string& id, const std::string& label=""):
      id_(id), label_(label), color_(UNHIGHLIGHT) {}
    const std::string& id() {return id_;}
    const std::string& label() {return label_;}
    const std::string& color() {return color_;}
    void set_label(const std::string& label) {label_ = label;}
    void set_color(const std::string& color) {color_ = color;}
    friend bool operator<(const VertexPair&, const VertexPair&);
  private:
    std::string id_;
    std::string label_;
    std::string color_;
  };

  class Edge {
  public:
    Edge(const std::string& v1, const std::string& v2, const std::string& label):
      v1_(v1), v2_(v2), label_(label), color_(UNHIGHLIGHT) {
    }
    const std::string& from() {return v1_;}
    const std::string& to() {return v2_;}
    const std::string& label() {return label_;}
    const std::string& color() {return color_;}
    void set_color(const std::string& color) {color_ = color;}
    friend bool operator<(const VertexPair&, const VertexPair&);
  private:
    std::string v1_;
    std::string v2_;
    std::string label_;
    std::string color_;
  };

 private:
  static const char* UNHIGHLIGHT;

  std::map<const std::string, Vertex*> vertices_;
  std::map<const VertexPair, Edge*> edges_;

  // Disallow copy & assign.
  GraphDraw(GraphDraw&);
  void  operator=(const GraphDraw&);
};


bool operator<(const GraphDraw::VertexPair& edge1, const GraphDraw::VertexPair& edge2);


#endif