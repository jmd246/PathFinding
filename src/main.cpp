#include <glad/glad.h>
#include <imgui.h>
#include<GLFW/glfw3.h>
#include<imgui_impl_opengl3.h>
#include<imgui_impl_glfw.h>
#include <iostream>
#include <Graph.hpp>
#include <GraphDrawer.hpp>
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






int main(){
    //initialize glfw
    Graph g;
    g.addEdge("a", "b");
    g.addEdge("a", "f");

    g.addEdge("b", "g");
    g.addEdge("b", "c");

    g.addEdge("c", "e");
    g.addEdge("c", "d");

    g.addEdge("d", "g");
    g.addEdge("d", "e");
    
    g.addEdge("e" , "f");
    
    g.addEdge("f", "g");
   







    GraphDrawer graphUI(g);


    
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


    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
       
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetWindowPos(ImVec2(0, 0), 0);
        ImGui::SetNextWindowSize(ImVec2(800, 600),0);
        ImGui::Begin("Construct Graph");
        graphUI.drawGraph();
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