#include <GraphDrawer.hpp>
GraphDrawer::GraphDrawer(Graph& g, float radius, float size) : graph(g), m_node_radius(radius), m_graph_size(size) {
	showResizeButton = false;
}

void GraphDrawer::drawGraphResizeButton() {
	float newSize = m_graph_size;
	ImGui::InputFloat("Graph Size", &newSize);
	if (newSize > 0) setGraphSize(newSize);
}

void GraphDrawer::drawGraph(const std::map<std::string, ImVec2>& positions) {
	drawGraphResizeButton();		
 	//get window offset
	ImVec2 windowPos = ImGui::GetWindowPos(); // top-left of this ImGui window
	//batch drawing commands in imguidrawlist
	ImDrawList* draw = ImGui::GetWindowDrawList();
	//draw edges
	for (const auto& [from, neighbors] : graph.m_adj_list) {
		if (!positions.count(from)) continue;

		ImVec2 fromPos = ImVec2(positions.at(from).x +  windowPos.x , positions.at(from).y + windowPos.y);

		for (const auto& edge : neighbors) {
			    //skip if missing a positon
				if (!positions.count(edge.to)) continue;
				ImVec2 toPos = ImVec2(positions.at(edge.to).x + windowPos.x, positions.at(edge.to).y + windowPos.y);
				draw->AddLine(fromPos, toPos, IM_COL32(200, 200, 200, 255), 2.0f);
				
				ImVec2 perp;
				ImVec2 direction = toPos - fromPos;
				float len = sqrtf(direction.x * direction.x + direction.y * direction.y);
				//skip division by zero
				if (len == 0) continue;
				//normalize
				direction.x /= len; direction.y /= len;
				perp = ImVec2(-direction.y, direction.x);
				
				if (graph.isDirected()) {
					
					float arrowSize = 10.0f;
					ImVec2 tip = toPos - (direction * m_node_radius);
					ImVec2 left = tip - direction * arrowSize + perp * (0.5f * arrowSize);
					ImVec2 right = tip - direction * arrowSize - perp * (0.5f * arrowSize);
					draw->AddTriangleFilled(tip, left, right , IM_COL32(200, 200, 200, 255));
				}

				//add edge weights 
				ImVec2 mid = (fromPos + toPos) * 0.5f;
				mid = mid + perp * m_weight_offset;

			
				char buf[16];
				snprintf(buf, sizeof(buf), "%d", edge.weight);
				draw->AddText(mid, IM_COL32(255,255, 0, 255), buf);
		}
	}
	//draw nodes
	for (const auto& [id,pos] : positions) {
		ImVec2 drawPos(pos.x + windowPos.x, pos.y + windowPos.y);
		draw->AddCircleFilled(drawPos, m_node_radius, IM_COL32(100, 200, 255, 255));

		ImFont* font = ImGui::GetFont();
		ImVec2 textSize = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.0f, id.c_str());
		ImVec2 textPos = ImVec2(drawPos.x - (textSize.x * 0.5f), drawPos.y - (textSize.y * 0.5f));
		draw->AddText(textPos, IM_COL32(0, 0, 0, 255), id.c_str());
	}
}
void GraphDrawer::drawGraph() {
	ImVec2 center = ImVec2( ImGui::GetWindowSize().x * 0.5f, ImGui::GetWindowSize().y * 0.5f);
	drawGraph(layoutCircle(center, m_graph_size));
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