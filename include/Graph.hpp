#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <map>
#include<iostream>
#include <string>
#include <set>



class Graph {
   bool m_directional;

public:

	struct Edge {
		std::string to;
		std::string from;
		int weight;
		// For std::set ordering
		bool operator<(const Edge& other) const {
			if (from != other.from) return from < other.from;
			if (to != other.to) return to < other.to;
			return weight < other.weight;
		}

	};
	bool isValid() const {
		return !m_adj_list.empty() || m_num_edges > 0;
	}
	bool isDirected() const { return m_directional; }
	void setDirected(bool val) { m_directional = val; }
	std::map<std::string, std::set<Edge> > m_adj_list;
	int m_num_edges;
	Graph(bool val = false ) : m_directional(val), m_num_edges(0) {}
	bool addEdge(std::string u, std::string v, int weight = 0);
	std::string print();
};
#endif 
