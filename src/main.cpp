#include <glad/glad.h>
#include <imgui.h>
#include<GLFW/glfw3.h>
#include<imgui_impl_opengl3.h>
#include<imgui_impl_glfw.h>
#include <iostream>
#include <Graph.hpp>
#include <GraphDrawer.hpp>
#include <GraphGenerator.hpp>
#include <GraphFileManager.hpp>
#include <PathFinder.hpp>
#include <imgui_stdlib.h>


void resizeWindowCallBack(GLFWwindow* window, int w, int h) {
    if (window == nullptr) return;
    glViewport(0, 0, w, h);
}
void processInput(GLFWwindow* window) {
    if (!window) return;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
Graph SampleGraph(bool isDirected) {
    Graph g(true);
    g.addEdge("b", "a", 9);
    g.addEdge("f", "a", 3);
    g.addEdge("e", "f", 8);
    g.addEdge("g", "f", 1);
    g.addEdge("c", "e", 1);
    g.addEdge("d", "e", 1);
    g.addEdge("d", "g", 4);
    g.addEdge("b", "g", 2);
    g.addEdge("c", "b", 8);
    g.addEdge("c", "d", 2);
    g.addEdge("g", "i", 4);
    g.addEdge("i", "a", 2);
    g.addEdge("i", "b", 8);
    g.addEdge("i", "d", 2);
    return g;
}


static bool showGraphWindow = false, showCreateNewGraph = false, showFileBrowser = false, showSaveDialog;
int main(){
    //initialize glfw
    Graph g = SampleGraph(true);
    
    GraphFileManager manager;

    GraphDrawer graphUI(g);
    GraphGenerator generator;
    PathFinder pathfinder(g);
   

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw";
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(1200, 800, "PathFinding", nullptr, nullptr);
    
    if (!window) {
        std::cerr << "Failed to create the window";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeWindowCallBack);
    glfwSwapInterval(1);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed to initialize glad";
        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }
    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    int scr_width, scr_height;

    bool showPathOutput = false;
    std::string outputPath;
    std::vector<std::string> path;
    std::unordered_map<std::string, int> dist;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
       
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glfwGetFramebufferSize(window, &scr_width, &scr_height);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar;
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(scr_width, scr_height), ImGuiCond_Always);

        ImGui::Begin("Main Menu",nullptr,window_flags);

        if (ImGui::BeginMenuBar()){
            if (ImGui::Button("Load Graph")) {
                ImGui::SetWindowFocus("Load Graph");
                showGraphWindow = true;
                showSaveDialog = false;
                manager.triggerLoadDialog();
            }
            if (ImGui::Button("New Graph")) {
                ImGui::SetNextWindowPos(ImVec2(0, 100), ImGuiCond_Always);
                ImGui::SetNextWindowSize(ImVec2(scr_width * 0.5f, scr_height * 0.5f));
                showCreateNewGraph = true;
            }
            if (ImGui::Button("Save Graph")  && graphUI.getGraph().isValid()) {
                showCreateNewGraph = false;
                ImGui::SetWindowFocus("Save Graph");
                g = graphUI.getGraph();
                manager.triggerSaveDialog();
                
            }
            ImGui::EndMenuBar();
        }
        
        static std::string start, end;
        bool input[2] = { ImGui::InputText("start", &start),
        ImGui::InputText("end", &end)
        };

        if (graphUI.getGraph().isValid()) {

            if (ImGui::Button("get path") && !start.empty() && !end.empty()) {
                dist = pathfinder.dijkstra(start);
                showPathOutput = true;
                path = pathfinder.reconstructPath(start, end);
                if (path.size() < 2) {
                    outputPath = "no path from " + start + " to " + end;
                    std::cout << outputPath;
                    //ImGui::Text("no path from %s to %s", start, end);
                }
                else {
                    outputPath = "";
                    int i = 0;
                    for (std::string node : path) {
                        if (i < path.size() - 1) {
                            outputPath += (node + ", ");
                        }
                        else {
                            outputPath += node;
                        }
                        i++;
                    }
                    //ImGui::Text( "%s", pathOutput.c_str());
                }
            }


            std::set<std::pair<std::string, std::string>> highlightedEdges;

            for (size_t i = 0; i + 1 < path.size(); i++) {
                highlightedEdges.insert({ path[i], path[i + 1] });
            }
            
            graphUI.drawGraph(highlightedEdges);
            pathfinder.setGraph(g);
            if (showCreateNewGraph) {
                generator.generateGraph(graphUI, manager,showCreateNewGraph);
            }

     
        }
       
        if (showPathOutput) {
            ImGui::Text("%s", outputPath.c_str());
            ImGui::Text("%i", dist[end]);
        }
        manager.processLoadDialog(g);
        manager.processSaveDialog(&g);
        ImGui::End();
        processInput(window);
        ImGui::Render();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

