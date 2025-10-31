#include "ImGUIWindow.h"
#include "Model.h"
#include "Practice.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "imgui.h"
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

void ImGUIWindow::render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  ImGuiIO &io = ImGui::GetIO();

  ImGui::ShowDemoWindow();

  // Your GUI code
  static bool showExtraInfo = false;
  ImGui::Begin("Light");
  { // Position
    ImGui::SeparatorText("Light Direction");
    ImGui::DragFloat("_X", &ProgramValues::dirLight.direction.r, 0.05f);
    ImGui::DragFloat("_Y", &ProgramValues::dirLight.direction.g, 0.05f);
    ImGui::DragFloat("_Z", &ProgramValues::dirLight.direction.b, 0.05f);
  }
  { // Ambient
    ImGui::SeparatorText("Ambient");
    static float a_value = ProgramValues::dirLight.ambient.r;
    ImGui::SliderFloat("Ambient Value", &a_value, 0.0f, 1.0f, "%.2f");

    ProgramValues::dirLight.ambient.r = a_value;
    ProgramValues::dirLight.ambient.g = a_value;
    ProgramValues::dirLight.ambient.b = a_value;
  }
  { // Diffuse
    ImGui::SeparatorText("Diffuse");
    static float d_value = ProgramValues::dirLight.diffuse.r;
    ImGui::SliderFloat("Diffuse Value", &d_value, 0.0f, 1.0f, "%.2f");

    ProgramValues::dirLight.diffuse.r = d_value;
    ProgramValues::dirLight.diffuse.g = d_value;
    ProgramValues::dirLight.diffuse.b = d_value;
  }
  { // Specular
    ImGui::SeparatorText("Specular");
    static float s_value = ProgramValues::dirLight.specular.r;
    ImGui::SliderFloat("Specular Value", &s_value, 0.0f, 1.0f, "%.2f");

    ProgramValues::dirLight.specular.r = s_value;
    ProgramValues::dirLight.specular.g = s_value;
    ProgramValues::dirLight.specular.b = s_value;
  }
  ImGui::End();

  ImGui::Begin("Object");
  {
    ImGui::SeparatorText("Properties");
    static float m_a_value = ProgramValues::model.ambient.r;
    ImGui::SliderFloat("Material Ambient Value", &m_a_value, 0.0f, 1.0f,
                       "%.2f");
    ImGui::DragFloat("Shininess", &ProgramValues::model.shininess, 1.0f, 1.0f,
                     256.0f, "%.1f");

    ProgramValues::model.ambient.r = m_a_value;
    ProgramValues::model.ambient.g = m_a_value;
    ProgramValues::model.ambient.b = m_a_value;
  }
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

void ImGUIWindow::clean() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}
