#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <map>
#include<iostream>
#include <string>
#include <set>

struct edge {
	std::string to;
	std::string from;
	int weight;
	// For std::set ordering
	bool operator<(const edge& other) const {
		if (from != other.from) return from < other.from;
		if (to != other.to) return to < other.to;
		return weight < other.weight;
	}

};

class Graph {
	bool m_directional;

public:
	bool isDirected() { return m_directional; }
	std::map<std::string, std::set<edge> > m_adj_list;
	int m_num_edges;
	Graph(bool val = false ) : m_directional(val), m_num_edges(0) {}
	bool addEdge(std::string u, std::string v, int weight = 0);
	std::string print();
};
#endif 
