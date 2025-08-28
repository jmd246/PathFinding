#ifndef GRAPH_DRAWER_HPP
#define GRAPH_DRAWER_HPP
#include <Graph.hpp>
#include <numbers>
#include <ImGui.h>
#include <map>
class GraphDrawer {
public:
	void drawGraph();
	GraphDrawer(Graph& g);
private:
	Graph& graph;
	void drawGraph(const std::map<std::string, ImVec2>& positions);
	std::map<std::string, ImVec2 > layoutCircle(ImVec2 center, float radius);


};

#endif