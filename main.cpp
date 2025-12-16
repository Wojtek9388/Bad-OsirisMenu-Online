#include <emscripten.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "osiris_gui.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

// ------------------------------------------------------------
// Globals
// ------------------------------------------------------------
static GLFWwindow* g_Window = nullptr;

// User hook for your ImGui code

int display_w = 1900;
int display_h = 1000;
FeaturesClass features;

// ------------------------------------------------------------
// Main loop
// ------------------------------------------------------------
void MainLoop()
{
    // Poll events
    glfwPollEvents();

    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Call user-defined GUI rendering
    RenderOsiris(&features);

    // Render ImGui
    ImGui::Render();

    // Get framebuffer size
    glfwGetFramebufferSize(g_Window, &display_w, &display_h);

    // Update viewport
    glViewport(0, 0, display_w, display_h);

    // Update ImGui IO display size (important for resizing)
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)display_w, (float)display_h);

    // Clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render ImGui draw data
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(g_Window);
}

// ------------------------------------------------------------
// Entry
// ------------------------------------------------------------
int main()
{
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Emscripten requires OpenGL ES
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window
    g_Window = glfwCreateWindow(1280, 720, "ImGui + Emscripten", nullptr, nullptr);
    if (!g_Window)
        return 1;

    glfwMakeContextCurrent(g_Window);
    glfwSwapInterval(1);

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Setup backends
    ImGui_ImplGlfw_InitForOpenGL(g_Window, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    // Main loop handled by Emscripten
    emscripten_set_main_loop(MainLoop, 0, true);

    // Cleanup (never reached in Emscripten unless you stop the loop)
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(g_Window);
    glfwTerminate();

    return 0;
}
