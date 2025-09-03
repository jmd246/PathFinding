#ifndef GRAPH_FILE_MANAGER_HPP
#define GRAPH_FILE_MANAGER_HPP
#include <nlohmann/json.hpp>
#include <Graph.hpp>
#include <ImGuiFileDialog.h>
#include <fstream>

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

public:
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