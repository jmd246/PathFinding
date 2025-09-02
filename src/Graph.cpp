#include <Graph.hpp>

bool Graph::addEdge(std::string u, std::string v, int weight) {
	//no negative weight
	if (weight <= 0) return false;
	//avoid self loops
	if (u == v) return false;



	//add edge from u to v
	if (m_adj_list[u].insert({ v,u,weight }).second) {
		if (!m_adj_list.count(u)) m_adj_list[u] = {};
		if (!m_adj_list.count(v)) m_adj_list[v] = {}; // ensures sink node is a key
		if (!m_directional) {
			m_adj_list[v].insert({ u,v,weight });
		}
		m_num_edges++;
		return true;
	}
	return false;
}

//function to print the adjaceny list rep of the graph
std::string Graph::print() {
	if (m_num_edges == 0) return "";
	std::string adjListOutput = "";
	for (auto i : m_adj_list) {
		adjListOutput.append(i.first + "<--");
		for (auto j : i.second) {
			adjListOutput.append(j.to + ", " + std::to_string(j.weight));
		}
		adjListOutput.append("\n");
	}
	return adjListOutput;
}



