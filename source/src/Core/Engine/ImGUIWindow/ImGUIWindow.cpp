#include "ImGUIWindow.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

const static constexpr char *OPENGL_VERSION = "#version 410";

ImGUIWindow::ImGUIWindow() {}

ImGUIWindow *ImGUIWindow::getInstance() {
  static ImGUIWindow instance;
  return &instance;
}

bool ImGUIWindow::init(SDL_Window *window, SDL_GLContext glContext) const {
  spdlog::info("ImGui initializing...");
  bool initSuccess = false;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport /
                                                      // Platform Windows
  // io.ConfigViewportsNoAutoMerge = true;
  // io.ConfigViewportsNoTaskBarIcon = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer backends
  // Setup Platform/Renderer backends
  if (!ImGui_ImplSDL2_InitForOpenGL(window, glContext)) {
    spdlog::error("Failed to initialize ImGui SDL2 backend.");
    initSuccess = false;
  }

  if (!ImGui_ImplOpenGL3_Init(OPENGL_VERSION)) {
    spdlog::error("Failed to initialize ImGui OpenGL3 backend.");
    initSuccess = false;
  }

  spdlog::info("ImGui initialized successfully.");
  initSuccess = true;
  return initSuccess;
}

void ImGUIWindow::createRootDockSpace() {
  ImGuiIO &io = ImGui::GetIO();
  IM_ASSERT(io.ConfigFlags & ImGuiConfigFlags_DockingEnable);

  ImGuiViewport *viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoDocking;

  ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  ImGui::Begin("MainDockSpaceWindow", nullptr, window_flags);
  ImGui::PopStyleVar(2);

  ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

  static bool first_time = true;
  if (first_time) {
    first_time = false;

    ImGui::DockBuilderRemoveNode(dockspace_id); // clear any existing layout
    ImGui::DockBuilderAddNode(
        dockspace_id,
        dockspace_flags |
            ImGuiDockNodeFlags_DockSpace); // creates a new dock node
    ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

    ImGuiID dock_main_id = dockspace_id;
    ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(
        dock_main_id, ImGuiDir_Left, 0.25f, nullptr, &dock_main_id);
    ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(
        dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);

    ImGui::DockBuilderDockWindow("Demo Window", dock_main_id);
    ImGui::DockBuilderDockWindow("Left Panel", dock_left_id);
    ImGui::DockBuilderDockWindow("Right Panel", dock_right_id);

    ImGui::DockBuilderFinish(dockspace_id);
  }

  ImGui::End();
}

void ImGUIWindow::render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  createRootDockSpace();

  ImGuiIO &io = ImGui::GetIO();

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoNavFocus;

  ImGui::ShowDemoWindow();

  // Your GUI code
  ImGui::Begin("Left Panel", nullptr, window_flags);
  ImGui::Text("Meow!");
  ImGui::End();

  ImGui::Begin("Right Panel", nullptr, window_flags);
  ImGui::Text("Meow!");
  ImGui::End();
  ImGui::Render();

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }
}

void ImGUIWindow::free() {
  spdlog::info("Destroying ImGUI resources...");
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  spdlog::info("ImGUI resources destroyed successfully.");
}
