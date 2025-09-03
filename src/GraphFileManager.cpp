#include <GraphFileManager.hpp>

// Open dialogs
void GraphFileManager::triggerLoadDialog() {
    ImGuiFileDialog::Instance()->OpenDialog("LoadGraphDlg", "Load Graph", ".json");
}
void GraphFileManager::triggerSaveDialog() {
    ImGuiFileDialog::Instance()->OpenDialog("SaveGraphDlg", "Save Graph", ".json");
}
void GraphFileManager::processLoadDialog(Graph& graph) {
    if (ImGuiFileDialog::Instance()->Display("LoadGraphDlg")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            graph = load_graph(filePath);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}
void GraphFileManager::save_graph(const Graph& g, const std::string& filePath) {
    if (!filePath.empty()) {
        json j;
        GraphFileManager::graph_to_json(j, g);
        std::ofstream file(filePath);
        if (!file) {
            // handle error
            return;
        }
        file << j.dump(4);
    }
}

Graph GraphFileManager::load_graph(const std::string& filePath) {
    Graph g;
    std::ifstream file(filePath);
    if (!file) {
        return g;
    }
    json j;
    file >> j;
    g.m_num_edges = j.at("num_edges");
    g.setDirected(j.at("directed"));
    g.m_adj_list.clear();
    for (auto& [node, edges_json] : j.at("adj_list").items()) {
        std::vector<Graph::Edge> edges_vec = edges_json.get<std::vector<Graph::Edge>>();
        g.m_adj_list[node] = std::set<Graph::Edge>(edges_vec.begin(), edges_vec.end());
    }
    return g;
}
void  GraphFileManager::processSaveDialog(const Graph& graph) {
    if (ImGuiFileDialog::Instance()->Display("SaveGraphDlg")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            save_graph(graph, filePath);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}
void GraphFileManager::graph_to_json(json& j, const Graph& g) {
    std::map<std::string, std::vector<Graph::Edge>> adj_vector;

    for (const auto& [node, edges_set] : g.m_adj_list) {
        // convert set to vector
        std::vector<Graph::Edge> edges_vec(edges_set.begin(), edges_set.end());
        adj_vector[node] = edges_vec;
    }
    const bool directed = g.isDirected();

    j.clear();
    j["directed"] = g.isDirected();
    j["num_edges"] = g.m_num_edges;
    j["adj_list"] = adj_vector; // now works thanks to to_json for Edge

}
