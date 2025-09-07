#include <PathFinder.hpp>


std::unordered_map<std::string, int> PathFinder::dijkstra(const std::string& start) {
	using p = std::pair<int, std::string>;
	
	std::priority_queue<p, std::vector<p>,std::greater<p> > p_queue;
	
	std::unordered_map<std::string, int> dist;
	explored.clear();
	
	//set all distance besides source to infinity  
	for (const auto& edge : m_graph.m_adj_list) {
		dist[edge.first] = std::numeric_limits<int>::max();
	}
	//put source distance 0
	dist[start] = 0;
	p_queue.push({ 0, start });

	while (!p_queue.empty()) {
		auto [distance,otherVertex] = p_queue.top();
		p_queue.pop();

		if (distance > dist[otherVertex]) continue;

		for (const auto& edge : m_graph.m_adj_list.at(otherVertex)) {
			//update distance
			int newDist = distance + edge.weight;
			//update if new minumum path is found
			if (newDist < dist[edge.to]) {
				dist[edge.to] = newDist;
				//update visited list
				explored[edge.to] = otherVertex;

				p_queue.push({ newDist,edge.to });
			}
		}
	}
	
	return dist;
}

std::vector<std::string> PathFinder::reconstructPath(const std::string& src, const std::string& target)
{
	std::vector<std::string> path;
	if (!explored.count(target)) return path; //no path
	for (std::string at = target; at != src; at = explored[at]) {
		path.push_back(at);
	}
	path.push_back(src);
	std::reverse(path.begin(), path.end());
	return path;
}

