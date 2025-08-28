#include <GraphDrawer.hpp>
GraphDrawer::GraphDrawer(Graph& g) : graph(g) {}
void GraphDrawer::drawGraph(const std::map<std::string, ImVec2>& positions) {
	//get window offset
	ImVec2 windowPos = ImGui::GetWindowPos(); // top-left of this ImGui window
	//batch drawing commands in imguidrawlist
	ImDrawList* draw = ImGui::GetWindowDrawList();
	//draw edges
	for (const auto& [u, neighbors] : graph.m_adj_list) {
		for (const auto& v : neighbors) {
			draw->AddLine(
				ImVec2( positions.at(u).x + windowPos.x, positions.at(u).y + windowPos.y),
				ImVec2(positions.at(v).x + windowPos.x, positions.at(v).y + windowPos.y),
				IM_COL32(200, 200, 200, 255),
				2.0f
			);
		}
	}
	//draw nodes
	for (const auto& [id,pos] : positions) {
		ImVec2 drawPos(pos.x + windowPos.x, pos.y + windowPos.y);
		draw->AddCircleFilled(drawPos, 50.0f, IM_COL32(100, 200, 255, 255));

		ImFont* font = ImGui::GetFont();
		ImVec2 textSize = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.0f, id.c_str());
		ImVec2 textPos = ImVec2(drawPos.x - (textSize.x * 0.5f), drawPos.y - (textSize.y * 0.5f));
		draw->AddText(textPos, IM_COL32(0, 0, 0, 255), id.c_str());
	}
}
void GraphDrawer::drawGraph() {
	ImVec2 center = ImVec2( ImGui::GetWindowSize().x * 0.5f, ImGui::GetWindowSize().y * 0.5f);
	drawGraph(layoutCircle(center, 150.f));
}

std::map<std::string, ImVec2> GraphDrawer::layoutCircle(ImVec2 center, float radius) {
	std::map<std::string, ImVec2> positions;

	//number of nodes
	int n = graph.m_adj_list.size();
	//node counter
	int i = 0;
	for (const auto& [node, _] : graph.m_adj_list) {
		//angle in rads of the node
		float angle = (2.0f * std::numbers::pi * i) / n;
		//position of the circle
		ImVec2 pos(center.x + radius * cos(angle), center.y + radius * sin(angle));

		positions[node] = pos;

		i++;
	}
	return positions;
}