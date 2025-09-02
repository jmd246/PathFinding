#include <glad/glad.h>
#include <nlohmann/json.hpp>
#include <imgui.h>
#include<GLFW/glfw3.h>
#include<imgui_impl_opengl3.h>
#include<imgui_impl_glfw.h>
#include <iostream>
#include <Graph.hpp>
#include <GraphDrawer.hpp>
#include <GraphGenerator.hpp>

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


static bool showGraphWindow = false, showCreateNewGraph;
int main(){
    //initialize glfw
    Graph g = SampleGraph(true);
    






    GraphDrawer graphUI(g);
    GraphGenerator generator;

    
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
                showGraphWindow = !showGraphWindow;
            }
            if (ImGui::Button("New Graph")) {
                showCreateNewGraph = !showCreateNewGraph;
            }
            ImGui::EndMenuBar();
        }       
        if (showGraphWindow) {
            graphUI.drawGraph();
        }
        if (showCreateNewGraph) {
            if (generator.generateGraph(graphUI)) {
                showGraphWindow = true;
            }
        }
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

