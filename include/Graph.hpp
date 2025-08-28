#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <map>
#include<iostream>
#include <list>
#include <string>
class Graph {
public:
	std::map<std::string, std::list<std::string> > m_adj_list;
	int m_num_edges;
	Graph();
	void addEdge(std::string u, std::string v);
	std::string print();

};
#endif 
