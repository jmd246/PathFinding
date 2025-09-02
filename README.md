# Graph Visualizer & Algorithm Playground
<img width="1918" height="1015" alt="Screenshot_progress_9-1-25" src="https://github.com/user-attachments/assets/4a19fe09-2fb6-4395-9b19-52523e0a9e90" />



A lightweight C++ project for constructing, visualizing, and experimenting with graphs and classical graph algorithms such as **Dijkstra**, **Prim’s**, **Kruskal’s**, **A\***, and graph coloring.  

This project provides a simple **ImGui-based UI** for graph creation and editing, with plans to add visualization for algorithms step-by-step.

---

## Features

- 🖱️ **Interactive UI** built with [Dear ImGui](https://github.com/ocornut/imgui)  
  - Menu bar for graph actions  
  - Form-based input for creating custom graphs  
- 📊 **Graph Representation**  
  - Stored as an adjacency list:  
    ```cpp
    std::map<std::string, std::set<edge>> m_adj_list;
    ```
  - `edge` includes `from`, `to`, and `weight`, with duplicate prevention  
- ✅ **Input Validation**  
  - Prevents duplicate edges  
  - Ensures vertex/edge constraints are respected  
- 📦 **Serialization** (WIP)  
  - Using [nlohmann/json](https://github.com/nlohmann/json) for saving & loading graphs  
- ⚡ **Algorithms (Planned)**  
  - Dijkstra’s shortest path  
  - Prim’s minimum spanning tree  
  - Kruskal’s minimum spanning tree  
  - A* pathfinding  
  - Graph coloring  

---

## Installation

### Dependencies
- [vcpkg](https://github.com/microsoft/vcpkg) for package management
- [Dear ImGui](https://github.com/ocornut/imgui)
- [nlohmann/json](https://github.com/nlohmann/json)

### Setup with vcpkg
```bash
# Install JSON library
vcpkg install nlohmann-json

# (Optional) integrate vcpkg with your system
vcpkg integrate install