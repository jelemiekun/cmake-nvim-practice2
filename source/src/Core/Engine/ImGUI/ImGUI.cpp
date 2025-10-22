// #include "imgui/imgui.h"
// #include "ImGUI.h"
// #include "imgui/imgui_impl_opengl3.h"
// #include "imgui/imgui_impl_sdl2.h"
// #include <SDL2/SDL.h>
// #include <glad/glad.h>
// #include <spdlog/spdlog.h>
//
// const static constexpr char *OPENGL_VERSION = "#version 430";
//
// ImGUI::ImGUI() {}
//
// ImGUI *ImGUI::getInstance() {
//   static ImGUI instance;
//   return &instance;
// }
//
// void ImGUI::init(SDL_Window *window, SDL_GLContext glContext) const {
//   spdlog::info("ImGui initializing...");
//
//   IMGUI_CHECKVERSION();
//   ImGui::CreateContext();
//   ImGuiIO &io = ImGui::GetIO();
//   (void)io;
//   io.ConfigFlags |=
//       ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
//   io.ConfigFlags |=
//       ImGuiConfigFlags_NavEnableGamepad;              // Enable Gamepad
//       Controls
//   io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
//   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable
//   Multi-Viewport /
//                                                       // Platform Windows
//   // io.ConfigViewportsNoAutoMerge = true;
//   // io.ConfigViewportsNoTaskBarIcon = true;
//
//   // Setup Dear ImGui style
//   ImGui::StyleColorsDark();
//   // ImGui::StyleColorsLight();
//
//   // When viewports are enabled we tweak WindowRounding/WindowBg so platform
//   // windows can look identical to regular ones.
//   ImGuiStyle &style = ImGui::GetStyle();
//   if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
//     style.WindowRounding = 0.0f;
//     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//   }
//
//   // Setup Platform/Renderer backends
//   // Setup Platform/Renderer backends
//   if (!ImGui_ImplSDL2_InitForOpenGL(window, glContext)) {
//     spdlog::error("Failed to initialize ImGui SDL2 backend.");
//     return;
//   }
//
//   if (!ImGui_ImplOpenGL3_Init(OPENGL_VERSION)) {
//     spdlog::error("Failed to initialize ImGui OpenGL3 backend.");
//     return;
//   }
//
//   spdlog::info("ImGui initialized successfully.");
// }
//
// void ImGUI::render() {
//   ImGui_ImplOpenGL3_NewFrame();
//   ImGui_ImplSDL2_NewFrame();
//   ImGui::NewFrame();
//
//   ImGuiIO &io = ImGui::GetIO();
//
//   ImGui::ShowDemoWindow();
//
//   // Your GUI code
//   static bool showExtraInfo = false;
//   ImGui::Begin("My Window");
//   ImGui::Text("Hello, world!");
//   if (ImGui::Button("Click me")) {
//     showExtraInfo = !showExtraInfo;
//   }
//
//   if (showExtraInfo) {
//     ImGui::Text("Extra FPS Info: %.1f", ProgramValues::GameWindow::FPS);
//   }
//   ImGui::End();
//
//   ImGui::Render();
//   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//   if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
//     SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();
//     SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
//     ImGui::UpdatePlatformWindows();
//     ImGui::RenderPlatformWindowsDefault();
//     SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
//   }
// }
//
// void ImGUI::clean() {
//   ImGui_ImplOpenGL3_Shutdown();
//   ImGui_ImplSDL2_Shutdown();
//   ImGui::DestroyContext();
// }
