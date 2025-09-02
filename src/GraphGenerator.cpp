#include <GraphGenerator.hpp>

void GraphGenerator::listVertices(const std::set<std::string>& allowedVertices) const {
	if (allowedVertices.size() == 0) return;
	
	std::string names;
	int i = 0;

	for (std::string name: allowedVertices) {
		if (i < allowedVertices.size() - 1) {
			names += (name + ", ") ;
		}
		else {
			names += name;
		}
		i++;
	}
	ImGui::Text(names.c_str());
}
bool GraphGenerator::generateGraph(GraphDrawer& graphUI) {
	graph_ready = true;
	ImGui::Begin("Create Graph");
	ImGui::InputInt("Number of vertices", &m_num_vertices);
	
	ImGui::Checkbox("Directed", &isDirected);

	if (isDirected) {
		m_max_edges = m_num_vertices * (m_num_vertices - 1);
	}
	else {
		m_max_edges = m_num_vertices * (m_num_vertices - 1) / 2;
	}
	
	if (edges.size() > m_max_edges) {
		edges.clear();
	}

	std::set<std::string> allowedVertices;
	for (int i = 0; i < m_num_vertices; i++) {
		std::string name = std::string(1, 'a' + i); // or ask user input
		allowedVertices.insert(name);
	}
	//show list of vertices
	listVertices(allowedVertices);

	// Buttons to add/remove edges dynamically
	if (ImGui::Button("Add Edge") && edges.size() < m_max_edges) {
		edges.push_back(EdgeInput{});
		ImGui::SameLine();
	}
	if (ImGui::Button("Remove Last Edge") && !edges.empty()) {
		edges.pop_back();
	}




	for (int i = 0; i < edges.size(); i++) {
		ImGui::PushID(i); // to avoid ID conflicts
		ImGui::Text("Edge %d", i + 1);
		ImGui::InputText("From", edges[i].from, IM_ARRAYSIZE(edges[i].from));
		ImGui::InputText("To", edges[i].to, IM_ARRAYSIZE(edges[i].to));
		ImGui::InputInt("Weight", &edges[i].weight);

		if (!allowedVertices.count(edges[i].from) || !allowedVertices.count(edges[i].to)) {
			ImGui::TextColored(ImVec4(255, 0, 0, 255), "Error: Invalid vertex name.\n");
			graph_ready = false;
		}

		ImGui::Separator();
		ImGui::PopID();
	}
	if (ImGui::Button("Create Graph") && graph_ready && !edges.empty()) {
		Graph customGraph(isDirected);
		for (auto& e : edges) {
			customGraph.addEdge(std::string(e.from), std::string(e.to), e.weight);
		}
		// Assign or update GraphDrawer
		graphUI.setGraph(customGraph);
		
	}
	if (ImGui::Button("Reset Edge List")) {
		edges.clear();
	}

	ImGui::End();
	return graph_ready;
}