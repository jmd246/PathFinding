#ifndef GRAPH_DRAWER_HPP
#define GRAPH_DRAWER_HPP
#include <Graph.hpp>
#include <numbers>
#include <ImGui.h>
#include <map>

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
	void setGraphSize(const float& size) { m_graph_size = size; }
	float getGraphSize() { return m_graph_size; }
	void drawGraph();
	GraphDrawer(Graph& g, float radius = 25.0f, float size = 150.0f);
	void setGraph(Graph& g) { graph = g; }
private:
	Graph& graph;
	bool showResizeButton;
	float m_node_radius, m_graph_size;
	void drawGraph(const std::map<std::string, ImVec2>& positions);
	void drawGraphResizeButton();
	std::map<std::string, ImVec2 > layoutCircle(ImVec2 center, float radius);





};

#endif