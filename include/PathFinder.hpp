#ifndef PATH_FINDER_HPP
#define PATH_FINDER_HPP
#include <unordered_map>
#include <vector>
#include <string>
#include <Graph.hpp>
#include <algorithm>
#include <queue>

class PathFinder {
public:
	PathFinder( Graph& g) : m_graph(g) {}
	void setGraph( Graph& g) { m_graph = g; }
	std::unordered_map<std::string, int> dijkstra(const std::string& start);
	std::vector<std::string> reconstructPath(const std::string& src, const std::string& target);
//prims
//kruskal
//a*
//bellman ford
private:
	Graph& m_graph;
	std::unordered_map<std::string, std::string> explored;


};
#endif ; // PATH_FINDER_HPP