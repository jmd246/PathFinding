#ifndef GRAPH_DRAWER_HPP
#define GRAPH_DRAWER_HPP
#include <Graph.hpp>
#include <numbers>
#include <ImGui.h>
#include <map>
// constraints on resize button
const static float MIN_GRAPH_SIZE = 200.0f, MAX_GRAPH_SIZE = 400.0f, MIN_NODE_RADIUS = 25.0f;


//inline helper functions for imgui vec2
inline ImVec2 operator-(const ImVec2& a, const ImVec2& b) {
	return ImVec2(a.x - b.x, a.y - b.y);
}
inline ImVec2 operator+(const ImVec2& a, const ImVec2& b) {
	return ImVec2(a.x + b.x, a.y + b.y);
}
inline ImVec2 operator*(const ImVec2& a, float s) {
	return ImVec2(a.x * s, a.y * s);
}
inline ImVec2 operator*(const ImVec2& a, const ImVec2& b) {
	return ImVec2(a.x * b.x, a.y * b.y);
}

class GraphDrawer {
public:
	void setGraphSize(const float& size) {
		if (size > MIN_GRAPH_SIZE && size < MAX_GRAPH_SIZE) {
			m_graph_size = size; 
		}
		else if (size > MAX_GRAPH_SIZE) {
			m_graph_size = MAX_GRAPH_SIZE;
		}
		else if (size < MIN_GRAPH_SIZE) {
			m_graph_size = MIN_GRAPH_SIZE;
		}
		else {
			return;
		}
	}
	float getGraphSize() const { return m_graph_size; }
	void drawGraph();
	GraphDrawer(Graph& g, float radius = MIN_NODE_RADIUS, float size = MIN_GRAPH_SIZE);
	void setGraph(Graph& g) { graph = g; }
private:
	Graph& graph;
	bool showResizeButton;
	float m_node_radius, m_graph_size;
	void drawGraph(const std::map<std::string, ImVec2>& positions);
	void drawGraphResizeButton();
	std::map<std::string, ImVec2 > layoutCircle(ImVec2 center, float radius);
	float m_weight_offset = 15.0f;
};
#endif