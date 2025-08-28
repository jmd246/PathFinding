#include <Graph.hpp>
Graph::Graph() : m_num_edges(0) {}

void Graph::addEdge(std::string u, std::string v) {
	//add edge from u to v
	m_adj_list[u].push_back(v);
	//add edge from v to u
	m_adj_list[v].push_back(u);
	m_num_edges++;
}

//function to print the adjaceny list rep of the graph
std::string Graph::print() {
	if (m_num_edges == 0) return "";
	std::string adjListOutput = "";
	for (auto i : m_adj_list) {
		adjListOutput.append(i.first + "<--");
		for (auto j : i.second) {
			adjListOutput.append(j + ", ");
		}
		adjListOutput.append("\n");
	}
	return adjListOutput;
}



