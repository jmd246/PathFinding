#ifndef GRAPH_FILE_MANAGER_HPP
#define GRAPH_FILE_MANAGER_HPP
#include <nlohmann/json.hpp>
#include <Graph.hpp>
#include <ImGuiFileDialog.h>
#include <ImGuiFileDialogConfig.h>
#include <fstream>
#include <filesystem>
#include<config.h>

using json = nlohmann::json;

namespace nlohmann {
   template<>
   struct adl_serializer<Graph::Edge> {
      static void to_json(json& j, const Graph::Edge& e) {

           j["from"] = e.from;
           j["to"] = e.to;
           j["weight"] = e.weight;
       }
      static void from_json(const json& j, Graph::Edge& e) {
           j.at("from").get_to(e.from);
           j.at("to").get_to(e.to);
           j.at("weight").get_to(e.weight);
       }
   };
}

    

class GraphFileManager {

private:
    IGFD::FileDialogConfig config;

    static std::string GetAssetsPath()
    {
        // Get current working directory
        std::filesystem::path assets(PROJECT_ROOT_DIR);

        // Append your assets/res folder
        assets /= "assets";   // or "assets"

        return assets.string(); // Convert to std::string
    }
public:
    GraphFileManager() {
        config.path = GetAssetsPath();
    }

    // Open dialogs
    void triggerLoadDialog(); 
    void triggerSaveDialog(); 

    // Call every frame inside ImGui loop
    void processLoadDialog(Graph& graph);

    void processSaveDialog(const Graph& graph);
  
   
    static void graph_to_json(json& j, const Graph& g);

    static Graph load_graph(const std::string& filePath);
    
    static void save_graph(const Graph& g, const std::string& filePath); 
};
#endif