#ifndef GRAPH_GENERATOR_HPP 
#define  GRAPH_GENERATOR_HPP 
#include <ImGui.h>
#include <GraphDrawer.hpp>
#include <GraphFileManager.hpp>
#include <vector>
class GraphGenerator
{
	struct EdgeInput {
		char from[16] = "";
		char to[16] = "";
		int weight = 1;
	};
public:
	bool generateGraph(GraphDrawer& graphUI, GraphFileManager& manager);
private:
	bool graph_ready;
	int m_num_vertices = 0;
	int m_max_edges = 0;
	std::vector<EdgeInput> edges;
	// state variables
	bool isDirected = false;

	//function to display set of names for vertices
	void listVertices(const std::set<std::string>& allowedVertices ) const;

};



#endif //  GRAPH_GENERATOR_HPP 
